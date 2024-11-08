#include <QtTest>
#include "Lights.h"

// add necessary includes here

class Lights_Test : public QObject
{
    Q_OBJECT

public:
    Lights_Test();
    ~Lights_Test();

private slots:
    void Lights_TurnOff();
    void Lights_TurnOn();
    void Save();
    void Load();

};

Lights_Test::Lights_Test() {}

Lights_Test::~Lights_Test() {}

void Lights_Test::Lights_TurnOff() {
    Lights lights = Lights();
    lights.turnOff();
    QCOMPARE(false,lights.isOn());
}

void Lights_Test::Lights_TurnOn() {
    Lights lights = Lights();
    lights.turnOn();
    QCOMPARE(true,lights.isOn());
}

void Lights_Test::Save(){
    Lights light = Lights();

    // Act
    light.Save("light.txt");

    // Assert
    QVERIFY(QFileInfo::exists("light.txt"));

    // Cleanup
    if (QFileInfo::exists("light.txt")) {
        QFile::remove("light.txt");
    }
}

void Lights_Test::Load(){
    Lights light = Lights();
    bool expectedValue = true;
    light.turnOn();
    light.Save("light.txt");
    light.turnOff();

    // Act
    light.Load("light.txt");

    // Assert
    QCOMPARE(light.isOn(), expectedValue);

    // Cleanup
    if (QFileInfo::exists("light.txt")) {
        QFile::remove("light.txt");
    }
}

QTEST_APPLESS_MAIN(Lights_Test)

#include "tst_lights_test.moc"
