#pragma once

#include <QString>
#include <QVector>
#include <QJsonObject>

// Forward declare
class DataObject;

class Property {
public:
	Property(QString key) {
		_key = key;
	}

	virtual ~Property() {}

	virtual QString GetKey() { return _key; }
	virtual void SetKey(QString key) { _key = key; }

	virtual QJsonObject ToJson() {
		QJsonObject result;
		result[GetKey()] = ToString();
		return result;
	}

	// For Objects, GetValue will return the string JSON representation.
	//    For values, it will return the value as a string.
	virtual QString ToString() = 0;
	virtual bool SetFrom(QString value) = 0;

	virtual DataObject* AsObject() { return nullptr; }
	virtual bool IsObject() { return false; }

private:
	QString _key;
};

/**
 * This class isn't meant to be used by itself but is meant to be a base class for 
 *		specific property implementations.  It can be used in 2 ways - you can pass
 *		it a pointer of the generic type T that it will get and set or you can let 
 *      this property class own the value.
 **/
template <typename T>
class PropertyImplBase : public Property {
public:
	PropertyImplBase(QString key) : Property(key) {
		_value = new T();
		_ownsValue = true;
	}

	PropertyImplBase(QString key, T initialValue) : Property(key) {
		_value = new T(initialValue);
		_ownsValue = true;
	}

	PropertyImplBase(QString key, T* prop) : Property(key) {
		_value = prop;
		_ownsValue = false;
	}

	virtual ~PropertyImplBase() {
		if (_ownsValue)
			delete _value;
	}

	T Get() {
		return *_value;
	}

	void Set(T newValue) {
		*_value = newValue;
	}

protected:
	T* _value = nullptr;
	bool _ownsValue = false;
};

class QStringProperty : public PropertyImplBase<QString> {
public:
	QStringProperty(QString key) : PropertyImplBase(key) {}
	QStringProperty(QString key, QString initialValue) : PropertyImplBase(key, initialValue) {}
	QStringProperty(QString key, QString* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() { 
		return *_value; 
	}

	virtual bool SetFrom(QString value) {
		*_value = value;
		return true;
	}
};

class Int32Property : public PropertyImplBase<int32_t> {
public:
	Int32Property(QString key) : PropertyImplBase(key) {}
	Int32Property(QString key, int32_t initialValue) : PropertyImplBase(key, initialValue) {}
	Int32Property(QString key, int32_t* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() {
		return QString::number(*_value);
	}

	virtual bool SetFrom(QString value) {
		bool result;
		int32_t newValue = value.toInt(&result, 10);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}
};

class Int64Property : public PropertyImplBase<int64_t> {
public:
	Int64Property(QString key) : PropertyImplBase(key) {}
	Int64Property(QString key, int64_t initialValue) : PropertyImplBase(key, initialValue) {}
	Int64Property(QString key, int64_t* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() {
		return QString::number(*_value);
	}

	virtual bool SetFrom(QString value) {
		// Note: qlonglong is always 64 bit in QT
		bool result;
		int64_t newValue = value.toLongLong(&result, 10);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}
};

class FloatProperty : public PropertyImplBase<float> {
public:
	FloatProperty(QString key) : PropertyImplBase(key) {}
	FloatProperty(QString key, float initialValue) : PropertyImplBase(key, initialValue) {}
	FloatProperty(QString key, float* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() {
		// The 2000 is the number of significant digits to allow
		//   Theoretically the max a double can have is 1074
		return QString::number(*_value, 'g', 2000);
	}

	virtual bool SetFrom(QString value) {
		bool result;
		float newValue = value.toFloat(&result);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}
};

class DoubleProperty : public PropertyImplBase<double> {
public:
	DoubleProperty(QString key) : PropertyImplBase(key) {}
	DoubleProperty(QString key, double initialValue) : PropertyImplBase(key, initialValue) {}
	DoubleProperty(QString key, double* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() {
		// The 2000 is the number of significant digits to allow
		//   Theoretically the max a double can have is 1074
		return QString::number(*_value, 'g', 2000);
	}

	virtual bool SetFrom(QString value) {
		bool result;
		double newValue = value.toDouble(&result);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}
};

class BooleanProperty : public PropertyImplBase<bool> {
public:
	BooleanProperty(QString key) : PropertyImplBase(key) {}
	BooleanProperty(QString key, bool initialValue) : PropertyImplBase(key, initialValue) {}
	BooleanProperty(QString key, bool* prop) : PropertyImplBase(key, prop) {}

	virtual QString ToString() {
		if (*_value)
			return QString("1");
		return QString("0");
	}

	virtual bool SetFrom(QString value) {
		if (value == "1") {
			*_value = true;
			return true;
		} else if (value == "0") {
			*_value = false;
			return true;
		}

		return false;			
	}
};
