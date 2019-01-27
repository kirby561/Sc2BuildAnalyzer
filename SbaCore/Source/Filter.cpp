#include "Filter.h"

Filter::Filter(QString name) : DataObject("Filter") {
	_name = name;

	AddProperty("Name", &name);
}

void Filter::ApplyFilter() {
	// ?? TODO
}
