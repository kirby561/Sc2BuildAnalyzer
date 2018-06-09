#pragma once

#include "Sc2EventIds.h"

class Sc2CreationEvent {
public:
	Sc2CreationEvent() {}

	double GetTimestampMs() { return GameLoop / GameLoopsPerSecond; }

	QString Event = "NNet.Replay.Tracker.SUnitBornEvent";
	QString EventId = Sc2EventId::SUnitBornEvent;

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
