#include "Build.h"

void Build::AddEntry(BuildEntry entry) {
	_buildOrder.append(entry);
}

std::pair<Build, Build> Build::FromReplay(Sc2Replay* replay) {
	Build player1Build(replay, 1);
	Build player2Build(replay, 2);
	const QVector<Sc2UnitEvent>* events = replay->GetEvents();
	for (auto eventItr = events->constBegin(); eventItr != events->end(); eventItr++) {
		Sc2Unit unit = Sc2Unit::CreateUnitByName(eventItr->UnitTypeName);

		// For now, just use buildings.  We'll want to 
		//    be a little more fancy later for how we
		//    decide to include things in builds.
		if (unit.IsValid() && unit.IsBuilding() && !unit.IsType(Sc2Unit::CreepTumor)) {
			Build* playerBuild = nullptr;
			if (eventItr->ControlPlayerId == 1)
				playerBuild = &player1Build;
			else if (eventItr->ControlPlayerId == 2)
				playerBuild = &player2Build;

			BuildEntry entry(unit, eventItr->GetTimestampSecs());
			playerBuild->AddEntry(entry);
		}
	}

	return std::make_pair(player1Build, player2Build);
}
