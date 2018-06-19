#pragma once

#include <QString>

// SC time is measured in GameLoops.
//    This converts between that and 
//    game seconds.
const double GameLoopsPerSecond = 22.4;

class Sc2EventId {
public:
	enum Sc2EventIds {
		Reserved0 = 0,
		SUnitBornEvent = 1,
		Reserved2 = 2,
		Reserved3 = 3,
		Reserved4 = 4,
		SUpgradeEvent = 5,
		SUnitInitEvent = 6,
		Reserved7 = 7,
		Reserved8 = 8,
		SPlayerSetupEvent = 9
	};

	/**
	* This table should match the above enum exactly.
	*/
	static QString EventIdTable[];
};
