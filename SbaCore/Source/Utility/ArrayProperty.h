#pragma once

#include "Property.h"
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>

// ArrayValueType must inherit from Property
template <typename IterableType, typename ArrayValueType>
class ArrayProperty : public Property {
public:
	ArrayProperty(QString key, IterableType* value) : Property(key) {
		_array = value;
	}
	
	virtual ~ArrayProperty() { 
		// ?? TODO: Who owns the properties in the array?  I think the owner of this class needs to.
	}

	virtual QJsonArray ToJsonArray() { 
		QJsonArray result;

		for (IterableType::iterator itr = _array->begin(); itr != _array->end(); itr++) {
			ArrayValueType* prop = *itr;
			if (prop->IsArray()) {
				result.append(prop->ToJsonArray());
			} else if (prop->IsObject()) {
				result.append(prop->ToJson());
			} else {
				result.append(prop->ToString());
			}
		}

		return result;
	}

	virtual bool SetFromArray(QJsonArray jsonArray) { 
		bool result = true;

		for (QJsonArray::iterator itr = jsonArray.begin(); itr != jsonArray.end(); itr++) {
			QJsonValueRef value = *itr;
			ArrayValueType* prop = new ArrayValueType();
			prop->SetKey(GetKey());
			if (value.isArray()) {
				prop->SetFromArray(value.toArray());
				_array->insert(_array->end(), prop);
			} else if (value.isObject()) {
				prop->SetFromJson(value.toObject());
				_array->insert(_array->end(), prop);
			} else if (value.isString()) {
				prop->SetFrom(value.toString());
				_array->insert(_array->end(), prop);
			} else {
				result = false;
			}
		}

		return result;
	}

	virtual bool IsArray() { 
		return true; 
	}

	// For Objects, GetValue will return the string JSON representation.
	//    For values, it will return the value as a string.
	virtual QString ToString() {
		QJsonDocument doc(ToJson());
		QString result(doc.toJson(QJsonDocument::Indented));
		return result;
	}

	virtual bool SetFrom(QString value) {
		QJsonDocument doc(QJsonDocument::fromJson(value.toUtf8()));
		if (!doc.isNull()) {
			if (doc.isArray()) {
				return SetFromArray(doc.array());
			}
		}

		return false;
	}

private:
	IterableType* _array = nullptr;
};
