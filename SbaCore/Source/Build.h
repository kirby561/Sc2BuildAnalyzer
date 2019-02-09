#pragma once

#include "ReplayData/ReplayData.h"
#include <QList>

class BuildEntry {
public:
	BuildEntry() {}

	BuildEntry(Sc2Unit unit, double timestampSecs) {
		Unit = unit;
		TimestampSecs = timestampSecs;
	}

	Sc2Unit Unit;
	double TimestampSecs = 0.0;
};

class Build {
public:
	Build() {}

	void AddEntry(BuildEntry entry);
	const QList<BuildEntry>& GetOrder() { return _buildOrder; }
	Sc2Replay* GetReplay() { return _replay; }

	/**
	 * Creates a pair of builds from the given replay.
	 * @param replay The replay to take the orders from.
	 * @return Returns a pair with the 2 build orders contained in the replay.  The first is for Player 1, the second is Player 2.
	 **/
	static std::pair<Build, Build> FromReplay(Sc2Replay* replay);

private:
	Build(Sc2Replay* replay, int playerId) {
		_replay = replay;
		_playerId = playerId;
	}

	QList<BuildEntry> _buildOrder;
	int _playerId = -1;
	Sc2Replay* _replay = nullptr;
};
