#include <QtTest>
#include "lifesupport.h"

// add necessary includes here

class LifeSupport_Tests : public QObject {
    Q_OBJECT

public:
    LifeSupport_Tests();
    ~LifeSupport_Tests();

private slots:
    void SetOxygen_WithPositiveValue_SetsOxygen();
    void SetOxygen_WithNegativeValue_ClampsOxygenTo0();
    void SetTemperature_WithAnyValue_SetsTemperature();
    void GetTempAsF_ReturnsTempInFahrenheit();
    void GetTempAsK_ReturnsTempInKelvin();
    void Save_CreatesNewFile();
    void Load_LoadsOxygenValue();
    void Load_LoadsTemperatureValue();
};

LifeSupport_Tests::LifeSupport_Tests() {}

LifeSupport_Tests::~LifeSupport_Tests() {}

void LifeSupport_Tests::SetOxygen_WithPositiveValue_SetsOxygen() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 0.f);
    float expected = 50.f;

    // Act
    ls.SetOxygen(50.f);

    // Assert
    QCOMPARE(ls.GetOxygen(), expected);
}

void LifeSupport_Tests::SetOxygen_WithNegativeValue_ClampsOxygenTo0() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 0.f);
    float expected = 0.f;

    // Act
    ls.SetOxygen(-5.f);

    // Assert
    QCOMPARE(ls.GetOxygen(), expected);
}

void LifeSupport_Tests::SetTemperature_WithAnyValue_SetsTemperature() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 0.f);
    float expected = 22.f;

    // Act
    ls.SetTemp(22.f);

    // Assert
    QCOMPARE(ls.GetTemp(), expected);
}

void LifeSupport_Tests::GetTempAsF_ReturnsTempInFahrenheit() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 5.f);
    float expected = 41.f;

    // Act
    float actual = ls.GetTempAsF();

    // Assert
    QCOMPARE(actual, expected);
}

void LifeSupport_Tests::GetTempAsK_ReturnsTempInKelvin() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 5.f);
    float expected = 278.15f;

    // Act
    float actual = ls.GetTempAsK();

    // Assert
    QCOMPARE(actual, expected);
}

void LifeSupport_Tests::Save_CreatesNewFile() {
    // Arrange
    LifeSupport ls = LifeSupport(0.f, 5.f);

    // Act
    ls.Save("lifesupport.txt");

    // Assert
    QVERIFY(QFileInfo::exists("lifesupport.txt"));

    // Cleanup
    if (QFileInfo::exists("lifesupport.txt")) {
        QFile::remove("lifesupport.txt");
    }
}

void LifeSupport_Tests::Load_LoadsOxygenValue() {
    // Arrange
    LifeSupport ls = LifeSupport(100.f, 22.f);
    float expectedValue = 100.f;
    ls.Save("lifesupport.txt");
    ls.SetOxygen(0.f);

    // Act
    ls.Load("lifesupport.txt");

    // Assert
    QCOMPARE(ls.GetOxygen(), expectedValue);

    // Cleanup
    if (QFileInfo::exists("lifesupport.txt")) {
        QFile::remove("lifesupport.txt");
    }
}

void LifeSupport_Tests::Load_LoadsTemperatureValue() {
    // Arrange
    LifeSupport ls = LifeSupport(100.f, 22.f);
    float expectedValue = 22.f;
    ls.Save("lifesupport.txt");
    ls.SetTemp(0.f);

    // Act
    ls.Load("lifesupport.txt");

    // Assert
    QCOMPARE(ls.GetTemp(), expectedValue);

    // Cleanup
    if (QFileInfo::exists("lifesupport.txt")) {
        QFile::remove("lifesupport.txt");
    }
}

QTEST_APPLESS_MAIN(LifeSupport_Tests)

#include "tst_lifesupport_tests.moc"
