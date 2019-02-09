#include "ReplayParser.h"
#include <QProcess>
#include <QStringList>
#include <QCoreApplication>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include "ReplayData/ReplayData.h"

ReplayParser::ReplayParser() {
}

ReplayParser::~ReplayParser() {
}

ReplayParseResult ReplayParser::Parse(QString replayPath) {
	QProcess parsingProcess;
	QString program(QCoreApplication::applicationDirPath() + "/SbaPythonReader.exe");
	QStringList arguments;
	arguments.append(replayPath);
	arguments.append("--trackerevents"); // ?? TODO: Provide different options for what data to get or get all of it
	arguments.append("--ndjson");
	parsingProcess.start(program, arguments);
	parsingProcess.waitForFinished();
	QString output(parsingProcess.readAllStandardOutput());
	QString errors(parsingProcess.readAllStandardError());
	int returnCode = parsingProcess.exitCode();
	if (returnCode != 0) {
		return ReplayParseResult(QString("Failed to read the replay file.  Error code: ") + returnCode + QString(" Error = ") + output + "\n\n" + errors, false);
	}

	Sc2Replay* replayData = new Sc2Replay(replayPath);
	QTextStream streamReader(&output);
	while (!streamReader.atEnd()) {
		QString nextObjectString = streamReader.readLine();
		QJsonParseError error;
		QJsonDocument document = QJsonDocument::fromJson(nextObjectString.toUtf8(), &error);
		if (document.isNull()) {
			// Just skip it but log
			Log::Error("There was a problem parsing the replay JSON: " + error.errorString().toStdString());
			continue;
		}

		// Check the type of event and add it to the replay data.
		if (document.isObject()) {
			QJsonObject obj = document.object();
			QJsonValue eventType = obj.value("_eventid");
			if (!eventType.isUndefined()) {
				Sc2EventId::Sc2EventIds eventId = (Sc2EventId::Sc2EventIds)eventType.toInt();
				if (eventId == Sc2EventId::SUnitBornEvent || eventId == Sc2EventId::SUnitInitEvent) {
					Sc2UnitEvent event(eventId);

					event.UnitTagIndex = GetInt64FromJson("m_unitTagIndex", obj);
					event.ControlPlayerId = GetInt64FromJson("m_controlPlayerId", obj);
					event.GameLoop = GetInt64FromJson("_gameloop", obj);
					event.Y = GetInt64FromJson("m_y", obj);
					event.X = GetInt64FromJson("m_x", obj);
					event.Bits = GetInt64FromJson("_bits", obj);
					event.UpkeepPlayerId = GetInt64FromJson("m_upkeepPlayerId", obj);
					event.UnitTypeName = GetStringFromJson("m_unitTypeName", obj);

					replayData->AddEvent(event);
				} else if (eventId == Sc2EventId::SPlayerSetupEvent) {
					Sc2Player player;
					player.PlayerId = GetInt64FromJson("m_playerId", obj);
					player.Type = GetInt64FromJson("m_type", obj);
					player.GameLoop = GetInt64FromJson("_gameloop", obj);
					player.Bits = GetInt64FromJson("_bits", obj);
					player.UserId = GetInt64FromJson("m_userId", obj);
					player.SlotId = GetInt64FromJson("m_slotId", obj);

					replayData->AddPlayer(player);
				}
			}
		}
	}

	if (returnCode != 0) {
		return ReplayParseResult(QString("An error occurred.  Code: ") + returnCode + QString(" Output: ") + output + QString(" Errors: ") + errors, false);
	}
	return ReplayParseResult(replayData);
}

int64_t ReplayParser::GetInt64FromJson(QString key, QJsonObject obj) {
	QJsonValue value = obj.value(key);
	if (!value.isUndefined()) {
		return value.toInt(-1);
	}
	return -1;
}

QString ReplayParser::GetStringFromJson(QString key, QJsonObject obj) {
	QJsonValue value = obj.value(key);
	if (!value.isUndefined()) {
		return value.toString();
	}
	return QString();
}
