#pragma once

#include <QString>

class Resources {
public:
	static void Init(QString resourceBasePath);
	static QString GetPath(QString resourcePath);

private:
	static QString _baseResourcePath;
};
