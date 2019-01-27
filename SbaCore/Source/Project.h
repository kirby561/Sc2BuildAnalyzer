#pragma once

#include <QString>
#include <QVector>
#include "ReplayData/ReplayData.h"
#include "Filter.h"
#include "DataObject.h"

class Project : public DataObject {
public:
	Project(QString name, QString directory);
	virtual ~Project() {}

	bool Save();
	static Project* Load(QString file);

private:
	QString _name;
	QString _directory;

	QVector<Sc2Replay*> _replays;
	QVector<Filter*> _filters;
	Filter* _rootFilter = nullptr;
};
