#include "Project.h"
#include "QFile"
#include "QDir"
#include "QDirIterator"
#include "QVector"
#include "ProgressListener.h"

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
