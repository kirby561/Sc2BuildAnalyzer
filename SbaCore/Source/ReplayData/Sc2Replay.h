#pragma once

#include "Sc2UnitEvent.h"
#include "Sc2Player.h"
#include <QVector>
#include <QFileInfo>
#include "DataObject.h"

class Sc2Replay : public DataObject {
public:
	Sc2Replay() : DataObject("Sc2Replay") { AddProperties(); }

	Sc2Replay(QString path) : DataObject("Sc2Replay") {
		_path = path;
		AddProperties();
	}

	void AddEvent(Sc2UnitEvent* event) {
		_events.append(event);
	}

	void AddPlayer(Sc2Player* player) {
		_players.append(player);
	}

	const QVector<Sc2UnitEvent*>* GetEvents() { return &_events; }
	QString GetName() {	return QFileInfo(_path).fileName();	}

private:
	QVector<Sc2UnitEvent*> _events;
	QVector<Sc2Player*> _players;
	QString _path; // Path relative to the project if this replay is part of a project

	void AddProperties() {
		AddProperty("Events", &_events);
		AddProperty("Players", &_players);
		AddProperty("Path", &_path);
	}
};
