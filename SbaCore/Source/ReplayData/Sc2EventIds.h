#pragma once

#include <QString>

// SC time is measured in GameLoops.
//    This converts between that and 
//    game seconds.
const double GameLoopsPerSecond = 22.4;

class Sc2EventId {
public:
	enum Sc2EventIds {
		SPlayerStatsEvent = 0,
		SUnitBornEvent = 1,
		SUnitDiedEvent = 2,
		SUnitOwnerChangeEvent = 3,
		SUnitTypeChangeEvent = 4,
		SUpgradeEvent = 5,
		SUnitInitEvent = 6,
		SUnitDoneEvent = 7,
		SUnitPositionsEvent = 8,
		SPlayerSetupEvent = 9
	};

	/**
	* This table should match the above enum exactly.
	*/
	static QString EventIdTable[];
};
