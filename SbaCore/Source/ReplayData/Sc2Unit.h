#pragma once

#include <QString>

class Sc2Unit {
public:
	enum UnitId {
		// Terran Units
		Scv,
		Marine,
		Reaper,
		Marauder,
		Ghost,
		Hellion,
		WidowMine,
		Cyclone,
		Tank,
		Thor,
		Viking,
		Medivac,
		Liberator,
		Raven,
		Banshee,
		BattleCruiser,
		Nuke,

		// Terran Buildings
		SupplyDepot,
		Barracks,
		Refinery,
		CommandCenter,
		EngineeringBay,
		Bunker,
		MissileTurret,
		SensorTower,
		TechLab,
		Reactor,
		Factory,
		Starport,
		GhostAcademy,
		Armory,
		FusionCore,

		// Protoss Units
		Probe,
		Zealot,
		Adept,
		Stalker,
		Sentry,
		HighTemplar,
		DarkTemplar,
		Archon,
		Observer,
		Immortal,
		Colossus,
		WarpPrism,
		Disruptor,
		Phoenix,
		Oracle,
		VoidRay,
		Carrier,
		Tempest,
		MothershipCore, // Rip
		Mothership,

		// Protoss Buildings
		Nexus,
		Pylon,
		Assimilator,
		Gateway,
		WarpGate, // Note: This is the building not the upgrade
		Forge,
		CyberneticsCore,
		PhotonCannon,
		ShieldBattery,
		RoboticsFacility,
		TwilightCouncil,
		RoboticsBay,
		FleetBeacon,
		TemplarArchives,
		DankShrine,

		// Zerg Units
		Drone,
		Queen,
		Zergling,
		Baneling,
		Roach,
		Ravager,
		Hydralisk,
		Lurker,
		Infestor,
		SwarmHost,
		Overlord,
		Overseer,
		Mutalisk,
		Corruptor,
		BroodLord,
		Viper,
		Ultralisk,

		// Zerg Buildings
		Hatchery,
		SpineCrawler,
		SporeCrawler,
		Extractor,
		SpawningPool,
		EvolutionChamber,
		RoachWarren,
		BanelingNest,
		Lair,
		HydraliskDen,
		LurkerDen,
		InfestationPit,
		Spire,
		NydusNetwork,
		Hive,
		GreaterSpire,
		UltraliskCavern,
		CreepTumor,

		// Count
		NumberOfUnits
	};

	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost);
	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, bool isBuilding);
	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost, bool isBuilding);

	// An array of all the units
	const Sc2Unit Units[];

private:
	UnitId _unitId;
	QString _unitName;
	int _buildTimeSecs;
	int _mineralCost;
	int _gasCost;
	float _supplyCost;
	bool _isBuilding;
};
