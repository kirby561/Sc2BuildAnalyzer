#include "Project.h"
#include "QFile"
#include "QDir"
#include "QDirIterator"
#include "QVector"
#include "ProgressListener.h"
#include "ReplayParser.h"
#include "Build.h"
#include "BuildComparator.h"

Project::Project(QString name, QString directory) : DataObject("Project") {
	_name = name;
	_directory = directory;

	AddProperties();

	_thread.Start();
}

void Project::AddProperties() {
	AddProperty("Name", &_name);
	AddProperty("RootFilter", &_rootFilterId);
}

QString Project::GetPath() {
	return _directory + "/" + _name + ".sba";
}

QString Project::GetReplayPath() {
	return _directory + "/Replays";
}

QString Project::GetFilterPath() {
	return _directory + "/Filters";
}

/**
 * Adds the replays from the given directory.
 * @param path The path to get the replays from.
 * @param listener Reports progress and indicates if the replays were successfully added or not.
 */
void Project::AddReplays(QString path, ProgressListener* listener) {
	QString replayPath = GetReplayPath();
	_thread.AddWork([path, replayPath, listener] {
		bool result = true;

		// Build a list of the files to copy
		QVector<QString> fileList;
		QDirIterator dirIterator(path, QDirIterator::Subdirectories);
		while (dirIterator.hasNext()) {
			QFile file(dirIterator.next());
			if (file.fileName().endsWith(".SC2Replay")) {
				QString filePath = QFileInfo(file).absoluteFilePath();
				fileList.append(filePath);
			}
		}

		int maxProgress = fileList.size();
		listener->OnProgressChanged(0, maxProgress);

		QDir sourceDir = QDir(path);
		for (int i = 0; i < fileList.size(); i++) {
			// Get the path relative to the source directory
			QString relativePath = sourceDir.relativeFilePath(fileList[i]);

			// Move it into the replays path with the same subpath
			QFile file(fileList[i]);
			QString newPath = replayPath + "/" + relativePath;
			QDir newDir = QFileInfo(newPath).absoluteDir();
			newDir.mkdir(".");
			if (!file.copy(newPath)) {
				Log::Warn(QString("Failed to copy %1").arg(fileList[i]).toStdString());
				result = false;
			}

			listener->OnProgressChanged(i + 1, maxProgress);
		}

		if (result)
			listener->OnFinished(0);
		else
			listener->OnFinished(-1);
	});
}

/**
 * Loads and parses all the replays of this project into memory.
 */
void Project::LoadReplays(ProgressListener* listener) {
	QString replayPath = GetReplayPath();
	_thread.AddWork([this, replayPath, listener] {
		// Clean up previous replays
		for (int i = 0; i < _replays.size(); i++)
			delete _replays[i];
		_replays.clear();

		bool result = true;

		QDirIterator dirIterator(replayPath, QDirIterator::Subdirectories);
		QVector<QString> fileList;
		while (dirIterator.hasNext()) {
			QFile file(dirIterator.next());
			if (file.fileName().endsWith(".SC2Replay")) {
				QString filePath = QFileInfo(file).absoluteFilePath();
				fileList.append(filePath);
			}
		}

		int maxProgress = fileList.size();
		listener->OnProgressChanged(0, maxProgress);

		ReplayParser parser(_directory);
		QDir replayDir(_directory);
		for (int i = 0; i < fileList.size(); i++) {
			QString path = replayDir.relativeFilePath(fileList[i]);

			// Parse the replay
			ReplayParseResult result = parser.Parse(path);
			if (result.Succeeded()) {
				_replays.append(result.GetReplay());
			} else {
				Log::Warn(QString("Could not parse replay %1 \n\tReason: %2").arg(path).arg(result.GetErrorDetails()).toStdString());
			}

			listener->OnProgressChanged(i + 1, maxProgress);
		}

		listener->OnFinished(0);
	});
}

// ?? Temp test method
void Project::ComputeReplayStats() {
	QVector<Build*> builds;
	for (int i = 0; i < _replays.size(); i++) {
		std::pair<Build*, Build*> replayBuilds = Build::FromReplay(_replays[i]);
		builds.append(replayBuilds.first);
		builds.append(replayBuilds.second);
	}

	QVector<QVector<Build*>> knownBuilds;
	QVector<int> editDistances;
	BuildComparator comparator;
	for (int i = 0; i < builds.size(); i++) {
		bool foundBuild = false;
		for (int y = 0; y < knownBuilds.size(); y++) {
			BuildComparison comparison = comparator.Compare(knownBuilds[y][0], builds[i]);
			editDistances.append(comparison.Result);

			if (abs(comparison.Result) < 1.1f) {
				knownBuilds[y].append(builds[i]);
				foundBuild = true;
				break;
			}
		}

		// If this is a new build, add it to the list
		if (!foundBuild) {
			QVector<Build*> known;
			known.append(builds[i]);
			knownBuilds.append(known);
		}
	}

	// Sort by occurences
	qSort(knownBuilds.begin(), knownBuilds.end(), [] (const QVector<Build*>& build1, const QVector<Build*>& build2) {
		return build1.size() < build2.size();
	});

	QFile file("E:/trash/builds.txt");
	file.open(QIODevice::WriteOnly);
	for (int i = 0; i < knownBuilds.size(); i++) {
		QString replays = "";
		for (int y = 0; y < knownBuilds[i].size(); y++) {
			replays += knownBuilds[i][y]->GetReplay()->GetName() + ", ";
		}
		int numOccurences = knownBuilds[i].size();

		QString line = QString("%1, %2, %3").arg(numOccurences).arg(knownBuilds[i][0]->GetOrder()[0]->Unit->GetUnitName()).arg(replays);
		file.write(line.toUtf8().constData());
		file.write("\n");
	}

	file.flush();
	file.close();

	Log::Message("Done");
}

void Project::PrintReplaysWithUnitByTime(Sc2Unit::UnitId unitId, double gameTime) {
	for (int i = 0; i < _replays.size(); i++) {
		Sc2Replay* replay = _replays[i];
		const QVector<Sc2UnitEvent*>* events = replay->GetEvents();

		double lairTiming = -1;
		double spireTiming = -1;
		double firstMutaTiming = -1;
		double numberOfGases = -1;
		double numberOfDrones = -1;
		for (QVector<Sc2UnitEvent*>::const_iterator itr = events->begin(); itr != events->end(); itr++) {
			Sc2UnitEvent* unitEvent = *itr;

			Sc2Unit* unit = Sc2Unit::CreateUnitByName(unitEvent->UnitTypeName);
			if (unit->IsValid()) {
				if (unitEvent->GetStartTime() <= gameTime) {
					if (unit->GetUnitId() == Sc2Unit::Mutalisk) {
						firstMutaTiming = unitEvent->GetStartTime();
						break;
					} else if (unit->GetUnitId() == Sc2Unit::Drone) {
						if (unitEvent->EventId == Sc2EventId::SUnitBornEvent)
							numberOfDrones++;
						else if (unitEvent->EventId == Sc2EventId::SUnitDiedEvent)
							numberOfDrones--; // ?? TODO: UnitDiedEvents dont have the name, just the ID so we need to find the unit.
					} else if (unit->GetUnitId() == Sc2Unit::Lair && lairTiming == -1) {
						lairTiming = unitEvent->GetStartTime();
					} else if (unit->GetUnitId() == Sc2Unit::Spire && spireTiming == -1) {
						spireTiming = unitEvent->GetStartTime();
					} else if (unit->GetUnitId() == Sc2Unit::Drone) {

					}
				} else {
					// We're done
					break;
				}
			}
		}
	}
}

/**
 * Saves the project to disk in the configured directory.  This is used to create the project initially too.
 * @return Returns true if it was saved successfully, false if there was an error.
 */
bool Project::Save() {
	// First make sure the directory exists
	QDir directory = QDir(_directory);
	if (!directory.exists()) {
		directory.mkdir(".");
	}

	QFile projectFile(GetPath());

	if (!projectFile.open(QIODevice::ReadWrite)) {
		Log::Error(QString("Failed to open the project file: %1").arg(projectFile.fileName()).toStdString());
		return false;
	}
	
	QByteArray bytes = ToString().toUtf8();
	int64_t bytesWritten = 0;
	while (bytesWritten < bytes.size()) {
		int64_t result = projectFile.write(ToString().toStdString().c_str());
		if (result < 0) {
			Log::Error(QString("An error occured writing %1 to disk.  Error: %2").arg(projectFile.fileName()).arg(result).toStdString());
			return false;
		}

		bytesWritten += result;
	}
	projectFile.close();

	// TODO: Save filters

	return true;
}

Project* Project::Load(QString file) {
	QFile projectFile(file);
	if (projectFile.open(QIODevice::ReadOnly)) {
		QString projectJson = QString::fromUtf8(projectFile.readAll());

		Project* project = new Project();
		if (project->SetFrom(projectJson)) {
			// ?? TODO: Load filters first.

			project->_directory = QFileInfo(projectFile).absolutePath();
			return project;
		} else {
			Log::Error(QString("Failed to parse project file: %1").arg(projectJson).toStdString());
			return nullptr;
		}
	} else {
		Log::Error(QString("File does not exist: %1").arg(file).toStdString());
		return nullptr;
	}
	
	return nullptr;
}
