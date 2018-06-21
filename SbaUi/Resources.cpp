#include "Resources.h"
#include "Log.h"

QString Resources::_baseResourcePath = "";

void Resources::Init(QString baseResourcePath) {
	_baseResourcePath = baseResourcePath;

	if (!_baseResourcePath.endsWith('/'))
		_baseResourcePath += '/';
}

QString Resources::GetPath(QString resourcePath) {
	if (_baseResourcePath.isEmpty()) {
		Log::Error("Resource path needs to be initialized with Resources::Init(...) before using resources.");
		std::abort();
	}

	return _baseResourcePath + resourcePath;
}
