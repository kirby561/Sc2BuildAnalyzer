#include "Project.h"

Project::Project(QString name, QString directory) : DataObject("Project") {
	_name = name;
	_directory = directory;

	AddProperty("Name", &_name);
	AddProperty("RootFilter", _rootFilter);
}
