#pragma once

// SC time is measured in GameLoops.
//    This converts between that and 
//    game seconds.
const double GameLoopsPerSecond = 22.4;

class Sc2EventId {
public:
	enum Sc2EventIds {
		SUnitBornEvent = 1,
		SUpgradeEvent = 5,
		SPlayerSetupEvent = 9
	};
};
