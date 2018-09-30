#pragma once

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include "Property.h"

/**
 * Data Objects at a basic level are objects with properties.
 *    This can be used to easily write/read objects to strings, files, and JSON objects.
 *    It also makes it easy to enumerate the properties of an object for things like searching.
 *    DataObjects are also properties themselves which means they can be nested.
 * 
 * This class can be used in 2 ways.
 *    1) The Property class implementations are used explicitly.  For example:
 *			class MyDataClass : public DataObject {
 *          public:
 *              Int32Property Length = Int32Property("Length", 0);
 *				
 *              MyDataClass() : DataObject {
 *                  AddProperty(&Length);
 *              }
 *          };
 *    2) The Property class implementations are used implicitly:
 *			class MyDataClass : public DataObject {
 *          public:
 *              MyDataClass() : DataObject {
 *                  AddProperty("Length", &_length);
 *              }
 *
 *          private:
 *              int32_t _length = 0;
 *          };
 *
 *    In both cases above, the Length property will be part of the known properties for MyDataClass.
 **/
class DataObject : public Property {
public:
	DataObject(QString key);
	virtual ~DataObject();

	virtual QJsonObject ToJson();
	virtual QString ToString();
	virtual bool SetFrom(QString value);
	virtual bool SetFromJson(QJsonObject json);
	virtual bool IsObject() { return true; }
	virtual DataObject* AsObject() { return this; }
	const QVector<Property*>& GetProperties() { return _properties; }

	// Specific types of properties
	void AddProperty(QString key, QString* prop) { AddProperty(new QStringProperty(key, prop), true); }
	void AddProperty(QString key, int32_t* prop) { AddProperty(new Int32Property(key, prop), true); }
	void AddProperty(QString key, int64_t* prop) { AddProperty(new Int64Property(key, prop), true); }
	void AddProperty(QString key, float* prop) { AddProperty(new FloatProperty(key, prop), true); }
	void AddProperty(QString key, double* prop) { AddProperty(new DoubleProperty(key, prop), true); }
	void AddProperty(QString key, bool* prop) { AddProperty(new BooleanProperty(key, prop), true); }

	void AddProperty(QString key, DataObject* prop) {
		prop->SetKey(key);
		AddProperty(prop);
	}

	void AddProperty(Property* prop, bool ownsProp = false) {
		_properties.append(prop);
		_propertyOwnership.append(ownsProp);
	}

private:
	// The following is the vector of our properties
	//   and another vector of the same size indicating
	//   if we own the corresponding property or not.
	QVector<Property*> _properties;
	QVector<bool> _propertyOwnership;
};
