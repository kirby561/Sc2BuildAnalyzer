#pragma once

#include "Sc2UnitEvent.h"
#include "Sc2Unit.h"
#include "Log.h"

double Sc2UnitEvent::GetTimestampSecs() const { 
	return GameLoop / GameLoopsPerSecond; 
}

double Sc2UnitEvent::GetStartTime() const {
	// Structures are started when a SUnitInitEvent is emitted
	// Units apparently are done when a SUnitBornEvent occurs so
	// we need to do math to figure out when it actually happened.
	Sc2Unit* unit = Sc2Unit::CreateUnitByName(UnitTypeName);
	if (unit->IsValid()) {
		// Valid means it's a unit or structure
		if (EventId == Sc2EventId::SUnitBornEvent) {
			return GetTimestampSecs() - unit->GetBuildTimeSecs();
		} else if (EventId == Sc2EventId::SUnitInitEvent) {
			return GetTimestampSecs();
		}
	} else if (IsUpgrade()) {
		return GetTimestampSecs();
	} else {
		Log::Error("GetStartTime: This method does not make sense if it is not a unit, structure or upgrade.");
		return -1;
	}
}

bool Sc2UnitEvent::IsUpgrade() const {
	return EventId == Sc2EventId::SUpgradeEvent;
}

void Sc2UnitEvent::AddProperties() {
	AddProperty("Event", &Event);
	AddProperty("UnitTagIndex", &UnitTagIndex);
	AddProperty("UnitTagRecycle", &UnitTagRecycle);
	AddProperty("ControlPlayerId", &ControlPlayerId);
	AddProperty("GameLoop", &GameLoop);
	AddProperty("Y", &Y);
	AddProperty("X", &X);
	AddProperty("Bits", &Bits);
	AddProperty("UpkeepPlayerId", &UpkeepPlayerId);
	AddProperty("UnitTypeName", &UnitTypeName);
}
