#include "UtilityTester.h"
#include "DataObject.h"

// Macro to make it easy to grab file/line for test failures.
#define LOG(MESSAGE) Log(QString("%1:%2: %3").arg(__FILE__).arg(__LINE__).arg(MESSAGE));

class TestSubObject : public DataObject {
public:
	TestSubObject(QString key) : DataObject(key) {
		_subProp1 = "SubProp1Value";
		_subProp2 = "SubProp2Value";

		AddProperty("SubProp1", &_subProp1);
		AddProperty("SubProp2", &_subProp2);
	}

	QString _subProp1;
	QString _subProp2;
};

class TestObject : public DataObject {
public:
	TestObject(QString key) : DataObject(key) {
		AddProperty("QStringProp", &_qStringProp);
		AddProperty("DoubleProp", &_doubleProp);
		AddProperty("FloatProp", &_floatProp);
		AddProperty("Int32Prop", &_int32Prop);
		AddProperty("Int64Prop", &_int64Prop);
		AddProperty("BooleanProp", &_booleanProp);
		AddProperty("TestSubObject", &_subObject);
		AddProperty("QStringArray", &_arrayOfStrings);
		AddProperty("ObjectsArray", &_arrayOfObjects);
	}

	QString _qStringProp = "QStringValue";
	double _doubleProp = 123.45678901234;
	float _floatProp = 123.4f;
	int32_t _int32Prop = INT32_MAX;
	int64_t _int64Prop = INT64_MAX;
	bool _booleanProp = false;
	TestSubObject _subObject = TestSubObject("TestSubObject");
	QVector<QStringProperty*> _arrayOfStrings;
	QVector<TestSubObject*> _arrayOfObjects;
};

bool UtilityTester::RunTests() {
	bool result = true;
	_log.clear();

	result &= TestDataObject();

	return result;
}

bool UtilityTester::TestDataObject() {
	bool result = true;

	// Make an object and go to a JSON string
	//   and back, then compare them to make
	//   sure all the values are correct.
	TestObject obj1("Obj1");
	
	// Add a bunch of strings to obj1's array
	int numStrings = 10;
	for (int i = 0; i < numStrings; i++) {
		obj1._arrayOfStrings.append(new QStringProperty("QStringArray", QString("QString %1").arg(i)));
	}

	int numObjectsInArray = 5;
	for (int i = 0; i < numObjectsInArray; i++) {
		TestSubObject* subObjForArray = new TestSubObject(QString("ArrayObj %1").arg(i));
		subObjForArray->_subProp1 = QString("ArrayObj %1 Prop 1").arg(i);
		subObjForArray->_subProp2 = QString("ArrayObj %1 Prop 2").arg(i);
		obj1._arrayOfObjects.append(subObjForArray);
	}

	QString jsonString = obj1.ToString();
	if (jsonString.isEmpty()) {
		result = false;
		LOG("Test object made an empty JSON string.");
	}

	// Read it back and make sure all the values
	//    are the same.
	TestObject obj2("Obj2");
	if (!obj2.SetFrom(jsonString)) {
		result = false;
		LOG("Failed to set a new TestObject from the JSON string of another.");
	}

	// Compare each value
	if (obj1._booleanProp != obj2._booleanProp) {
		result = false;
		LOG("Boolean properties did not match after reading from JSON string.");
	}

	if (obj1._doubleProp != obj2._doubleProp) {
		result = false;
		LOG("Double properties did not match after reading from JSON string.");
	}

	if (obj1._floatProp != obj2._floatProp) {
		result = false;
		LOG("Float properties did not match after reading from JSON string.");
	}

	if (obj1._int32Prop != obj2._int32Prop) {
		result = false;
		LOG("Int32 properties did not match after reading from JSON string.");
	}

	if (obj1._int64Prop != obj2._int64Prop) {
		result = false;
		LOG("Int64 properties did not match after reading from JSON string.");
	}

	if (obj1._qStringProp != obj2._qStringProp) {
		result = false;
		LOG("QString properties did not match after reading from JSON string.");
	}

	// Check that the sub objects are the same:
	if (obj1._subObject._subProp1 != obj2._subObject._subProp1) {
		result = false;
		LOG("Sub object prop 1 was not the same");
	}

	if (obj1._subObject._subProp2 != obj2._subObject._subProp2) {
		result = false;
		LOG("Sub object prop 2 was not the same");
	}

	// Compare all the strings in the string array
	if (obj2._arrayOfStrings.size() != numStrings) {
		result = false;
		LOG("Object did not have the right number of strings in the array.");
	} else {
		for (int i = 0; i < numStrings; i++) {
			QString obj1String = obj1._arrayOfStrings[i]->Get();
			QString obj2String = obj2._arrayOfStrings[i]->Get();
			if (obj1String != obj2String) {
				result = false;
				LOG(QString("Object strings array at index %1 was not the same.  Obj1 had %2, Obj2 had %3.")
								.arg(i).arg(obj1String).arg(obj2String));
			}
		}
	}

	return result;
}

// Logging methods
void UtilityTester::Log(QString message) {
	_log.append(message);
}
