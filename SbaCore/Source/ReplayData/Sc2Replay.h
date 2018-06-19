#pragma once

#include "Sc2UnitEvent.h"
#include "Sc2Player.h"
#include <QVector>

class Sc2Replay {
public:
	Sc2Replay() {}

	void AddEvent(Sc2UnitEvent event) {
		_events.append(event);
	}

	void AddPlayer(Sc2Player player) {
		_players.append(player);
	}

	const QVector<Sc2UnitEvent>* GetEvents() { return &_events; }

private:
	QVector<Sc2UnitEvent> _events;
	QVector<Sc2Player> _players;
};
