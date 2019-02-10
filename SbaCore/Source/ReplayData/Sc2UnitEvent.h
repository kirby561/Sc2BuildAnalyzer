#pragma once

#include "Sc2EventIds.h"
#include <QString>
#include "DataObject.h"

class Sc2UnitEvent : public DataObject {
public:
	Sc2UnitEvent() : DataObject() { AddProperties(); }

	Sc2UnitEvent(Sc2EventId::Sc2EventIds id) : DataObject(Sc2EventId::EventIdTable[id]) {
		Event = Sc2EventId::EventIdTable[id];
		EventId = id;
		AddProperties();
	}

	double GetTimestampSecs() const { return GameLoop / GameLoopsPerSecond; }

	QString Event;
	Sc2EventId::Sc2EventIds EventId;

	int64_t UnitTagIndex = -1;
	int64_t UnitTagRecycle = -1;
	int64_t ControlPlayerId = -1;
	int64_t GameLoop = 0;
	int64_t Y = 0;
	int64_t X = 0;
	int64_t Bits = 0;
	int64_t UpkeepPlayerId = -1;
	QString UnitTypeName;

private:
	void AddProperties() {
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
};
