#pragma once

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

// Helper macro for creating the constructors of each property type
#define PROPERTY_CONSTRUCTORS(NAME, TYPE) \
public: \
NAME##Property(QString key) : PropertyImplBase(key) {} \
NAME##Property(QString key, TYPE initialValue) : PropertyImplBase(key, initialValue) {} \
NAME##Property(QString key, TYPE* prop) : PropertyImplBase(key, prop) {} \
 \
protected: \
	template <typename IterableType, typename ArrayValueType> \
	friend class ArrayProperty; \
	NAME##Property() {} \


// Forward declare
class DataObject;
template <typename IterableType, typename ArrayValueType>
class ArrayProperty;

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

	virtual bool SetFromJson(QJsonObject value) {
		if (value[GetKey()].isString()) {
			SetFrom(value[GetKey()].toString());
			return true;
		}
		return false;
	}

	// We are not an array but derived classes may be.
	virtual QJsonArray ToJsonArray() { return QJsonArray();	}
	virtual bool SetFromArray(QJsonArray jsonArray) { return false; }
	virtual bool IsArray() { return false; }

	// For Objects, GetValue will return the string JSON representation.
	//    For values, it will return the value as a string.
	virtual QString ToString() = 0;
	virtual bool SetFrom(QString value) = 0;

	virtual DataObject* AsObject() { return nullptr; }
	virtual bool IsObject() { return false; }
	

protected:
	// DataObjects and ArrayProperties need access to 
	//    the default constructor.  Otherwise we need
	//    to require DataObjects to have a QString key constructor
	//    which sometimes conflicts with other uses of a QString constructor.
	friend class DataObject;
	template <typename IterableType, typename ArrayValueType>
	friend class ArrayProperty;
	Property() {}

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

	PropertyImplBase() {
		_value = new T();
		_ownsValue = true;
	}
};

class QStringProperty : public PropertyImplBase<QString> {
public:
	virtual QString ToString() { 
		return *_value; 
	}

	virtual bool SetFrom(QString value) {
		*_value = value;
		return true;
	}

	PROPERTY_CONSTRUCTORS(QString, QString)
};

class Int32Property : public PropertyImplBase<int32_t> {
public:
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

	PROPERTY_CONSTRUCTORS(Int32, int32_t)
};

class UInt32Property : public PropertyImplBase<uint32_t> {
public:
	virtual QString ToString() {
		return QString::number(*_value);
	}

	virtual bool SetFrom(QString value) {
		bool result;
		uint32_t newValue = value.toUInt(&result, 10);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}

	PROPERTY_CONSTRUCTORS(UInt32, uint32_t)
};

class Int64Property : public PropertyImplBase<int64_t> {
public:
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

	PROPERTY_CONSTRUCTORS(Int64, int64_t)
};

class UInt64Property : public PropertyImplBase<uint64_t> {
public:
	virtual QString ToString() {
		return QString::number(*_value);
	}

	virtual bool SetFrom(QString value) {
		// Note: qulonglong is always 64 bit in QT
		bool result;
		uint64_t newValue = value.toULongLong(&result, 10);

		// Only update the value if the parsing was successful
		if (result)
			*_value = newValue;

		return result;
	}

	PROPERTY_CONSTRUCTORS(UInt64, uint64_t)
};

class FloatProperty : public PropertyImplBase<float> {
public:
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

	PROPERTY_CONSTRUCTORS(Float, float)
};

class DoubleProperty : public PropertyImplBase<double> {
public:
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

	PROPERTY_CONSTRUCTORS(Double, double)
};

class BooleanProperty : public PropertyImplBase<bool> {
public:
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

	PROPERTY_CONSTRUCTORS(Boolean, bool)
};
