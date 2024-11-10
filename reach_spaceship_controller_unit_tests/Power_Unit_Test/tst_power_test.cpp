#include <QtTest>
#include "power.h"

class Power_test : public QObject
{
    Q_OBJECT

public:
    Power_test();
    ~Power_test();

private slots:
    void test_initialValues();
    void test_setPowerLevel();
    void test_setPowerStatus();
    void test_saveAndLoad();
};

Power_test::Power_test() {}

Power_test::~Power_test() {}

// Test the initial values of the Power object
void Power_test::test_initialValues() {
    Power power;
    QCOMPARE(power.GetPower(), 0.0f);  // Expect initial power level to be 0.0
    QCOMPARE(power.IsOn(), false);     // Expect initial power status to be off
}

// Test setting and getting the power level
void Power_test::test_setPowerLevel() {
    Power power;
    power.SetPower(75.0f);             // Set power level to 75.0
    QCOMPARE(power.GetPower(), 75.0f);  // Verify the power level is set correctly
}

// Test setting and getting the power on/off status
void Power_test::test_setPowerStatus() {
    Power power;
    power.SetOn(true);                 // Turn on the power
    QCOMPARE(power.IsOn(), true);       // Verify power is on
    power.SetOn(false);                // Turn off the power
    QCOMPARE(power.IsOn(), false);      // Verify power is off
}

// Test saving and loading the power state
void Power_test::test_saveAndLoad() {
    Power power;
    power.SetPower(50.0f);             // Set power level to 50.0
    power.SetOn(true);                 // Turn on the power

    QString fileName = "power_test.txt";
    power.Save(fileName);              // Save the current state to a file

    Power loadedPower;
    loadedPower.Load(fileName);        // Load the state from the file

    QCOMPARE(loadedPower.GetPower(), 50.0f); // Verify power level is loaded correctly
    QCOMPARE(loadedPower.IsOn(), true);      // Verify power status is loaded correctly
}

QTEST_APPLESS_MAIN(Power_test)

#include "tst_power_test.moc"
