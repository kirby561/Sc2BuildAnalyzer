#pragma once

#include "Sc2EventIds.h"

class Sc2Player {
public:
	Sc2Player() {}

	double GetTimestampMs() { return GameLoop / GameLoopsPerSecond; }

	QString Event = "NNet.Replay.Tracker.SPlayerSetupEvent";
	int64_t EventId = Sc2EventId::SPlayerSetupEvent;

	int64_t PlayerId = -1;
	int64_t Type = -1;
	int64_t GameLoop = -1;
	int64_t Bits = -1;
	int64_t UserId = -1;
	int64_t SlotId = -1;
};
