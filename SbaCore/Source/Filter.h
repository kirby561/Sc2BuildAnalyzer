#pragma once

#include <QString>
#include "ReplayData/ReplayData.h"
#include "DataObject.h"

class Filter : public DataObject {
public:
	Filter(QString name);

	void ApplyFilter();

private:
	QString _name;
	Filter* _parent = nullptr;
	QVector<Filter*> _children;
	QVector<Sc2Replay*> _filteredReplays;
};
