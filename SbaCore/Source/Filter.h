#pragma once

#include <QString>
#include "ReplayData/ReplayData.h"

class Filter {
public:
	Filter(QString name);

	void ApplyFilter();

private:
	QString _name;
	Filter* _parent = nullptr;
	QVector<Filter*> _children;
	QVector<Sc2Replay*> _filteredReplays;
};
