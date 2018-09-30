#include "DataObject.h"

DataObject::DataObject(QString key) : Property(key) {
	_properties.reserve(20);
	_propertyOwnership.reserve(20);
}

DataObject::~DataObject() {
	for (int i = 0; i < _properties.length(); i++) {
		if (_propertyOwnership[i])
			delete _properties[i];
	}
	_properties.clear();
}

QJsonObject DataObject::ToJson() {
	QJsonObject result;

	for (int i = 0; i < _properties.length(); i++) {
		if (_properties[i]->IsObject())
			result[_properties[i]->GetKey()] = _properties[i]->ToJson();
		else
			result[_properties[i]->GetKey()] = _properties[i]->ToString();
	}

	return result;
}

QString DataObject::ToString() {
	QJsonDocument doc(ToJson());
	QString result(doc.toJson(QJsonDocument::Indented));
	return result;
}

bool DataObject::SetFrom(QString value) {
	QJsonDocument doc(QJsonDocument::fromJson(value.toUtf8()));
	if (!doc.isNull()) {
		if (doc.isObject()) {
			return SetFromJson(doc.object());
		}
	}

	return false;
}

bool DataObject::SetFromJson(QJsonObject json) {
	// Try to read all the properties
	// ?? TODO: We can add a way to have a "lenient read" which allows missing properties.
	//    Right now it is strict and just returns if a property is not present
	for (QVector<Property*>::iterator propItr = _properties.begin(); propItr != _properties.end(); propItr++) {
		Property* prop = *propItr;
		QJsonValueRef jsonValueRef = json[prop->GetKey()];
		if (prop->IsObject() && jsonValueRef.isObject()) {
			DataObject* propObject = dynamic_cast<DataObject*>(prop);
			if (!propObject->SetFromJson(jsonValueRef.toObject())) {
				return false;
			}
		} else if (jsonValueRef.isString()) {
			if (!prop->SetFrom(jsonValueRef.toString())) {
				return false;
			}
		} else {
			return false; // Type mismatch
		}
	}

	return true;
}
