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

QTEST_APPLESS_MAIN(Lights_Test)

#include "tst_lights_test.moc"
