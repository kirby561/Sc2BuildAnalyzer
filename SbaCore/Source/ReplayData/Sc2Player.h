#pragma once

#include "Sc2EventIds.h"
#include "DataObject.h"

class Sc2Player : public DataObject {
public:
	Sc2Player() : DataObject("Sc2Player") {
		AddProperty("Event", &Event);
		AddProperty("EventId", &EventId);
		AddProperty("PlayerId", &PlayerId);
		AddProperty("Type", &Type);
		AddProperty("GameLoop", &GameLoop);
		AddProperty("Bits", &Bits);
		AddProperty("UserId", &UserId);
		AddProperty("SlotId", &SlotId);
	}

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
