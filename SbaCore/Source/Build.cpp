#include "Build.h"

Build::~Build() {
	for (auto buildItr = _buildOrder.begin(); buildItr != _buildOrder.end(); buildItr++) {
		BuildEntry* entry = *buildItr;
		delete entry;
	}
	_buildOrder.clear();
}

void Build::AddEntry(BuildEntry* entry) {
	_buildOrder.append(entry);
}

std::pair<Build*, Build*> Build::FromReplay(Sc2Replay* replay) {
	Build* player1Build = new Build(replay, 1);
	Build* player2Build = new Build(replay, 2);
	const QVector<Sc2UnitEvent*>* events = replay->GetEvents();
	for (auto eventItr = events->constBegin(); eventItr != events->end(); eventItr++) {
		Sc2UnitEvent* unitEvent = *eventItr;
		Sc2Unit* unit = Sc2Unit::CreateUnitByName(unitEvent->UnitTypeName);

		// For now, just use buildings.  We'll want to 
		//    be a little more fancy later for how we
		//    decide to include things in builds.
		if (unit->IsValid() && unit->IsBuilding() && !unit->IsType(Sc2Unit::CreepTumor)) {
			Build* playerBuild = nullptr;
			if (unitEvent->ControlPlayerId == 1)
				playerBuild = player1Build;
			else if (unitEvent->ControlPlayerId == 2)
				playerBuild = player2Build;
			else {
				// For now, only support 2 players.
				continue;
			}

			BuildEntry* entry = new BuildEntry(unit, unitEvent->GetTimestampSecs());
			playerBuild->AddEntry(entry);
		}
	}

	return std::make_pair(player1Build, player2Build);
}
