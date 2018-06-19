#include "Build.h"

void Build::AddEntry(BuildEntry entry) {
	_buildOrder.append(entry);
}

Build Build::FromReplay(Sc2Replay* replay) {
	Build result;
	const QVector<Sc2CreationEvent>* events = replay->GetEvents();
	for (auto eventItr = events->constBegin(); eventItr != events->end(); eventItr++) {
		Sc2Unit unit = Sc2Unit::CreateUnitByName(eventItr->UnitTypeName);

		// For now, just use buildings.  We'll want to 
		//    be a little more fancy later for how we
		//    decide to include things in builds.
		if (unit.IsValid() && unit.IsBuilding()) {
			BuildEntry entry(unit, eventItr->GetTimestampSecs());
			result.AddEntry(entry);
		}
	}

	return result;
}
