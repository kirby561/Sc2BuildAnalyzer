#pragma once

#include "Sc2Unit.h"

Sc2Unit* Sc2Unit::Units[] = {
	// Terran Units
	new Sc2Unit(Scv, "SCV", 12, 50, 0, 1, false),
	new Sc2Unit(Marine, "Marine", 12, 50, 0, 1, false),
	new Sc2Unit(Reaper, "Reaper", 32, 50, 50, 1, false),
	new Sc2Unit(Marauder, "Marauder", 21, 100, 25, 2, false),
	new Sc2Unit(Ghost, "Ghost", 29, 200, 100, 2, false),
	new Sc2Unit(Hellion, "Hellion", 21, 100, 0, 2, false),
	new Sc2Unit(WidowMine, "WidowMine", 21, 75, 25, 2, false),
	new Sc2Unit(Cyclone, "Cyclone", 32, 150, 100, 3, false),
	new Sc2Unit(SiegeTank, "SiegeTank", 32, 150, 125, 3, false),
	new Sc2Unit(Thor, "Thor", 43, 300, 200, 6, false),
	new Sc2Unit(Viking, "VikingFighter", 30, 150, 75, 2, false),
	new Sc2Unit(Medivac, "Medivac", 30, 100, 100, 2, false),
	new Sc2Unit(Liberator, "Liberator", 43, 150, 100, 3, false),
	new Sc2Unit(Raven, "Raven", 43, 100, 200, 2, false),
	new Sc2Unit(Banshee, "Banshee", 43, 150, 100, 3, false),
	new Sc2Unit(BattleCruiser, "Battlecruiser", 64, 400, 300, 6, false),
	new Sc2Unit(Nuke, "Nuke", 43, 100, 100, 0, false),
	
	// Terran Buildings
	new Sc2Unit(SupplyDepot, "SupplyDepot", 21, 100, 0, true),
	new Sc2Unit(Barracks, "Barracks", 46, 150, 0, true),
	new Sc2Unit(Refinery, "Refinery", 21, 75, 0, true),
	new Sc2Unit(CommandCenter, "CommandCenter", 71, 400, 0, true),
	new Sc2Unit(EngineeringBay, "EngineeringBay", 25, 125, 0, true),
	new Sc2Unit(Bunker, "Bunker", 29, 100, 0, true),
	new Sc2Unit(MissileTurret, "MissileTurret", 18, 100, 0, true),
	new Sc2Unit(SensorTower, "SensorTower", 18, 125, 100, true),
	new Sc2Unit(TechLab, "TechLab", 18, 50, 25, true),
	new Sc2Unit(Reactor, "Reactor", 36, 50, 50, true),
	new Sc2Unit(Factory, "Factory", 43, 150, 100, true),
	new Sc2Unit(Starport, "Starport", 36, 150, 100, true),
	new Sc2Unit(GhostAcademy, "GhostAcademy", 29, 150, 50, true),
	new Sc2Unit(Armory, "Armory", 46, 150, 100, true),
	new Sc2Unit(FusionCore, "FusionCore", 46, 150, 150, true),

	// Protoss Units
	new Sc2Unit(Probe, "Probe", 12, 50, 0, 1, false),
	new Sc2Unit(Zealot, "Zealot", 27, 100, 0, 2, false),
	new Sc2Unit(Adept, "Adept", 27, 100, 25, 2, false),
	new Sc2Unit(Stalker, "Stalker", 30, 125, 50, 2, false),
	new Sc2Unit(Sentry, "Sentry", 26, 50, 100, 2, false),
	new Sc2Unit(HighTemplar, "HighTemplar", 39, 50, 150, 2, false),
	new Sc2Unit(DarkTemplar, "DarkTemplar", 39, 125, 125, 2, false),
	new Sc2Unit(Archon, "Archon", 9, 0, 0, 4, false),
	new Sc2Unit(Observer, "Observer", 21, 25, 75, 1, false),
	new Sc2Unit(Immortal, "Immortal", 39, 250, 100, 4, false),
	new Sc2Unit(Colossus, "Colossus", 54, 300, 200, 6, false),
	new Sc2Unit(WarpPrism, "WarpPrism", 36, 200, 0, 2, false),
	new Sc2Unit(Disruptor, "Disruptor", 36, 150, 150, 3, false),
	new Sc2Unit(Phoenix, "Phoenix", 25, 150, 100, 2, false),
	new Sc2Unit(Oracle, "Oracle", 37, 150, 150, 3, false),
	new Sc2Unit(VoidRay, "VoidRay", 43, 250, 150, 4, false),
	new Sc2Unit(Carrier, "Carrier", 86, 350, 250, 6, false),
	new Sc2Unit(Tempest, "Tempest", 43, 300, 200, 6, false),
	new Sc2Unit(MothershipCore, "MothershipCore", 21, 100, 100, 2, false),
	new Sc2Unit(Mothership, "Mothership", 114, 400, 400, 8, false),

	// Protoss Buildings
	new Sc2Unit(Nexus, "Nexus", 71, 400, 0, true),
	new Sc2Unit(Pylon, "Pylon", 18, 100, 0, true),
	new Sc2Unit(Assimilator, "Assimilator", 21, 75, 0, true),
	new Sc2Unit(Gateway,"Gateway", 46, 150, 0, true),
	new Sc2Unit(WarpGate, "WarpGate", 7, 0, 0, true),
	new Sc2Unit(Forge, "Forge", 32, 150, 0, true),
	new Sc2Unit(CyberneticsCore, "CyberneticsCore", 36, 150, 0, true),
	new Sc2Unit(PhotonCannon, "PhotonCannon", 29, 150, 0, true),
	new Sc2Unit(ShieldBattery, "ShieldBattery", 29, 100, 0, true),
	new Sc2Unit(RoboticsFacility, "RoboticsFacility", 46, 200, 100, true),
	new Sc2Unit(TwilightCouncil, "TwilightCouncil", 36, 150, 150, true),
	new Sc2Unit(RoboticsBay, "RoboticsBay", 46, 200, 200, true),
	new Sc2Unit(FleetBeacon, "FleetBeacon", 43, 300, 200, true),
	new Sc2Unit(TemplarArchives, "TemplarArchives", 36, 150, 200, true),
	new Sc2Unit(DankShrine, "DarkShrine", 71, 150, 150, true),
	new Sc2Unit(Stargate, "Stargate", 43, 150, 150, true),
	
	// Zerg Units
	new Sc2Unit(Drone, "Drone", 12, 50, 0, 1, false),
	new Sc2Unit(Queen, "Queen", 36, 150, 0, 2, false),
	new Sc2Unit(Zergling, "Zergling", 17, 50, 0, 1, false),
	new Sc2Unit(Baneling, "Baneling", 14, 25, 25, 0.5f, false),
	new Sc2Unit(Roach, "Roach", 19, 75, 25, 2, false),
	new Sc2Unit(Ravager, "Ravager", 9, 25, 75, 3, false),
	new Sc2Unit(Hydralisk, "Hydralisk", 24, 100, 50, 2, false),
	new Sc2Unit(Lurker, "Lurker", 18, 50, 100, 3, false),
	new Sc2Unit(Infestor, "Infestor", 36, 100, 150, 2, false),
	new Sc2Unit(SwarmHost, "SwarmHost", 29, 100, 75, 3, false),
	new Sc2Unit(Overlord, "Overlord", 18, 100, 0, 0, false),
	new Sc2Unit(Overseer, "Overseer", 12, 50, 50, 0, false),
	new Sc2Unit(Mutalisk, "Mutalisk", 24, 100, 100, 2, false),
	new Sc2Unit(Corruptor, "Corruptor", 29, 150, 100, 2, false),
	new Sc2Unit(BroodLord, "BroodLord", 24, 150, 150, 4, false),
	new Sc2Unit(Viper, "Viper", 29, 100, 200, 3, false),
	new Sc2Unit(Ultralisk, "Ultralisk", 39, 300, 200, 6, false),

	// Zerg Buildings
	new Sc2Unit(Hatchery, "Hatchery", 71, 300, 0, true),
	new Sc2Unit(SpineCrawler, "SpineCrawler", 36, 100, 0, true),
	new Sc2Unit(SporeCrawler, "SporeCrawler", 21, 75, 0, true),
	new Sc2Unit(Extractor, "Extractor", 21, 25, 0, true),
	new Sc2Unit(SpawningPool, "SpawningPool", 46, 200, 0, true),
	new Sc2Unit(EvolutionChamber, "EvolutionChamber", 25, 75, 0, true),
	new Sc2Unit(RoachWarren, "RoachWarren", 39, 150, 0, true),
	new Sc2Unit(BanelingNest, "BanelingNest", 43, 100, 50, true),
	new Sc2Unit(Lair, "Lair", 57, 150, 100, true),
	new Sc2Unit(HydraliskDen, "HydraliskDen", 29, 100, 100, true),
	new Sc2Unit(LurkerDen, "LukerDen", 86, 100, 100, true),
	new Sc2Unit(InfestationPit, "InfestationPit", 36, 100, 100, true),
	new Sc2Unit(Spire, "Spire", 71, 200, 200, true),
	new Sc2Unit(NydusNetwork, "NydusNetwork", 36, 150, 200, true),
	new Sc2Unit(Hive, "Hive", 71, 200, 150, true),
	new Sc2Unit(GreaterSpire, "GreaterSpire", 71, 100, 150, true),
	new Sc2Unit(UltraliskCavern, "UltraliskCavern", 46, 150, 200, true),
	new Sc2Unit(CreepTumor, "CreepTumor", 11, 0, 0, true),
	new Sc2Unit(Invalid, "Invalid", 0, 0, 0, true)
};

QHash<QString, Sc2Unit*> Sc2Unit::_unitMap = QHash<QString, Sc2Unit*>();

Sc2Unit::Sc2Unit() 
	: Sc2Unit(Invalid, "Invalid", 0, 0, 0, 0, true) {
}

Sc2Unit::Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost)
	: Sc2Unit(unitId, unitName, buildTimeSecs, mineralCost, gasCost, supplyCost, false) {
}

Sc2Unit::Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, bool isBuilding)
	: Sc2Unit(unitId, unitName, buildTimeSecs, mineralCost, gasCost, 0, isBuilding) {
}

Sc2Unit::Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost, bool isBuilding) {
	_unitId = unitId;
	_unitName = unitName;
	_buildTimeSecs = buildTimeSecs;
	_mineralCost = mineralCost;
	_gasCost = gasCost;
	_supplyCost = supplyCost;
	_isBuilding = isBuilding;

	AddProperties();
}

void Sc2Unit::InitUnitTable() {
	for (int i = 0; i < NumberOfUnits; i++) {
		_unitMap.insert(Units[i]->GetUnitName(), Units[i]);
	}
}

Sc2Unit* Sc2Unit::CreateUnitByName(QString unitName) {
	auto unitItr = _unitMap.find(unitName);
	if (unitItr != _unitMap.end()) {
		return *unitItr;
	}

	return Units[Invalid];
}