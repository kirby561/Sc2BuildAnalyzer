#pragma once

#include "ReplayData/ReplayData.h"
#include "DataObject.h"
#include <QList>

class BuildEntry : public DataObject {
public:
	BuildEntry() { 
		Unit = new Sc2Unit();
		AddProperties(); 
	}

	BuildEntry(Sc2Unit* unit, double timestampSecs) {
		Unit = unit;
		TimestampSecs = timestampSecs;

		AddProperties();
	}

	~BuildEntry() {
		delete Unit;
	}

	Sc2Unit* Unit = nullptr;
	double TimestampSecs = 0.0;

protected:
	void AddProperties() {
		AddProperty("Unit", Unit);
		AddProperty("TimestampSecs", &TimestampSecs);
	}
};

class Build : public DataObject {
public:
	Build() { AddProperties(); }
	~Build();

	void AddEntry(BuildEntry* entry);
	const QList<BuildEntry*>& GetOrder() { return _buildOrder; }
	Sc2Replay* GetReplay() { return _replay; }

	/**
	 * Creates a pair of builds from the given replay.
	 * @param replay The replay to take the orders from.
	 * @return Returns a pair with the 2 build orders contained in the replay.  The first is for Player 1, the second is Player 2.
	 **/
	static std::pair<Build*, Build*> FromReplay(Sc2Replay* replay);

private:
	QList<BuildEntry*> _buildOrder;
	int _playerId = -1;
	Sc2Replay* _replay = nullptr;

	Build(Sc2Replay* replay, int playerId) {
		_replay = replay;
		_playerId = playerId;

		AddProperties();
	}

	// Disable copying
	Build(const Build& other) {}

	void AddProperties() {
		AddProperty("BuildOrder", &_buildOrder);
		AddProperty("PlayerId", &_playerId);
		// ?? TODO: Add a replay ID or something so we can get the pointer back.
	}
};
