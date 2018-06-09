#pragma once

#include "Sc2CreationEvent.h"
#include "Sc2Player.h"
#include <QVector>

class Sc2Replay {
public:
	Sc2Replay() {}

	void AddEvent(Sc2CreationEvent sc2CreationEvent) {
		_creationEvents.append(sc2CreationEvent);
	}

	void AddPlayer(Sc2Player player) {
		_players.append(player);
	}

private:
	QVector<Sc2CreationEvent> _creationEvents;
	QVector<Sc2Player> _players;
};
