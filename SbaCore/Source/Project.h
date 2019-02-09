#pragma once

#include <QString>
#include <QVector>
#include "ReplayData/ReplayData.h"
#include "Filter.h"
#include "DataObject.h"
#include "WorkQueueThread.h"
#include "ProgressListener.h"

class Project : public DataObject {
public:
	Project(QString name, QString directory);
	virtual ~Project() { _thread.Stop(); }

	QString GetPath();
	QString GetReplayPath();
	QString GetFilterPath();

	void AddReplays(QString path, ProgressListener* listener);
	void LoadReplays(ProgressListener* listener);
	void ComputeReplayStats();
	bool Save();
	static Project* Load(QString file);

private:
	Project() : DataObject("Project") { AddProperties(); }
	void AddProperties();

	QString _name;
	QString _rootFilterId;
	QString _directory;

	QVector<Sc2Replay*> _replays;
	QVector<Filter*> _filters;
	Filter* _rootFilter = nullptr;

	WorkQueueThread _thread; // Thread for project operations to happen on
};
