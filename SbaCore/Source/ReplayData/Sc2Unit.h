#pragma once

#include <QString>
#include <QHash>
#include "Log.h"
#include "DataObject.h"

class Sc2Unit : public DataObject {
public:
	enum UnitId : uint32_t {
		// Terran Units
		Scv,
		Marine,
		Reaper,
		Marauder,
		Ghost,
		Hellion,
		WidowMine,
		Cyclone,
		SiegeTank,
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
		Stargate,

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

		// Invalid
		Invalid,

		// Count
		NumberOfUnits
	};

	Sc2Unit();
	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost);
	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, bool isBuilding);
	Sc2Unit(UnitId unitId, QString unitName, int buildTimeSecs, int mineralCost, int gasCost, float supplyCost, bool isBuilding);

	UnitId GetUnitId() const { return _unitId; }
	QString GetUnitName() const { return _unitName; }
	int GetBuildTimeSecs() const { return _buildTimeSecs; }
	int GetMineralCost() const { return _mineralCost; }
	int GetGasCost() const { return _gasCost; }
	float GetSupplyCost() const { return _supplyCost; }
	bool IsBuilding() const { return _isBuilding; }	
	bool IsValid() const { return _unitId != Invalid; }
	bool IsType(UnitId unitId) { return _unitId == unitId; }

	/**
	 * This should be called before mapping names to units.  This initializes
	 *    the table that does the mapping.
	 **/
	static void InitUnitTable();

	/**
	 * Creates an Sc2Unit of the given name.
	 * @param unitName The name of the unit to find.
	 * @returns Returns the created unit or Units[Invalid] if the name did not match a known unit.
	 **/
	static Sc2Unit* CreateUnitByName(QString unitName);

private:
	UnitId _unitId;
	QString _unitName;
	int _buildTimeSecs;
	int _mineralCost;
	int _gasCost;
	float _supplyCost;
	bool _isBuilding;

	// A mapping of Unit Name to Sc2Unit
	static QHash<QString, Sc2Unit*> _unitMap;
	
	// An array of all the units
	static Sc2Unit* Units[];

	void AddProperties() {
		AddProperty("UnitId", (uint32_t*)&_unitId);
		AddProperty("UnitName", &_unitName);
		AddProperty("BuildTimeSecs", &_buildTimeSecs);
		AddProperty("MineralCost", &_mineralCost);
		AddProperty("GasCost", &_gasCost);
		AddProperty("SupplyCost", &_supplyCost);
		AddProperty("IsBuilding", &_isBuilding);
	}

	// Don't allow copy constructor
	Sc2Unit(const Sc2Unit& other) {}
};
