#pragma once

#include "Sc2EventIds.h"
#include <QString>

class Sc2UnitEvent {
public:
	Sc2UnitEvent() {}

	Sc2UnitEvent(Sc2EventId::Sc2EventIds id) {
		Event = Sc2EventId::EventIdTable[id];
		EventId = id;
	}

	double GetTimestampSecs() const { return GameLoop / GameLoopsPerSecond; }

	QString Event;
	Sc2EventId::Sc2EventIds EventId;

	int64_t UnitTagIndex = -1;
	int64_t UnitTagRecycle = -1;
	void* CreatorUnitTagRecycle = nullptr;
	int64_t ControlPlayerId = -1;
	void* CreatorAbilityName = nullptr;
	int64_t GameLoop = 0;
	int64_t Y = 0;
	int64_t X = 0;
	int64_t Bits = 0;
	int64_t UpkeepPlayerId = -1;
	QString UnitTypeName;
	void* CreatorUnitTagIndex = nullptr;
};
