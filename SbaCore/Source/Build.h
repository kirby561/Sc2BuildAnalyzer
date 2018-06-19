#pragma once

#include "ReplayData/ReplayData.h"
#include <QList>

class BuildEntry {
public:
	BuildEntry(Sc2Unit unit, double timestampSecs) {
		Unit = unit;
		TimestampSecs = timestampSecs;
	}

	Sc2Unit Unit;
	double TimestampSecs;
};

class Build {
public:
	Build() { }

	void AddEntry(BuildEntry entry);
	const QList<BuildEntry>& GetOrder() { return _buildOrder; }

	/**
	 * Creates a build from the given replay.
	 * @param replay The replay to take the order from.
	 **/
	static Build FromReplay(Sc2Replay* replay);

private:
	QList<BuildEntry> _buildOrder;

};
