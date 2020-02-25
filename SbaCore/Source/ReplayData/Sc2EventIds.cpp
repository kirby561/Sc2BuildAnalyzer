#include "Sc2EventIds.h"

/**

Some notes about the events below:
	SUnitBornEvent's are emitted when non-building units are completed.  There is no special message for units began training so we need to calculate it
					from other information like build time and chrono times.
	SUnitDiedEvent's are emitted when units or buildings die.
	SUnitInitEvent's are emitted when buildings are started.
	SUnitDoneEvent's are emitted when builds finish.
	SUnitTypeChangeEvent are emitted when things transform like hatch-->Lair, larva to egg, egg to unit.

**/
QString Sc2EventId::EventIdTable[] = {
	"NNet.Replay.Tracker.SPlayerStatsEvent",
	"NNet.Replay.Tracker.SUnitBornEvent",
	"NNet.Replay.Tracker.SUnitDiedEvent",
	"NNet.Replay.Tracker.SUnitOwnerChangeEvent",
	"NNet.Replay.Tracker.SUnitTypeChangeEvent",
	"NNet.Replay.Tracker.SUpgradeEvent",
	"NNet.Replay.Tracker.SUnitInitEvent",
	"NNet.Replay.Tracker.SUnitDoneEvent",
	"NNet.Replay.Tracker.SUnitPositionsEvent",
	"NNet.Replay.Tracker.SPlayerSetupEvent"
};
