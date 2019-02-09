#pragma once

#include "Sc2UnitEvent.h"
#include "Sc2Player.h"
#include <QVector>
#include <QFileInfo>

class Sc2Replay {
public:
	Sc2Replay(QString path) {
		_path = path;
	}

	void AddEvent(Sc2UnitEvent event) {
		_events.append(event);
	}

	void AddPlayer(Sc2Player player) {
		_players.append(player);
	}

	const QVector<Sc2UnitEvent>* GetEvents() { return &_events; }
	QString GetName() {	return QFileInfo(_path).fileName();	}

private:
	QVector<Sc2UnitEvent> _events;
	QVector<Sc2Player> _players;
	QString _path;
};
