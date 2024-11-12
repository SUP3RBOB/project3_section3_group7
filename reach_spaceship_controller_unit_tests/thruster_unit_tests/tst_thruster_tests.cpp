#include <QtTest>
#include "thruster.h"

// add necessary includes here

class Thruster_Tests : public QObject {
    Q_OBJECT

public:
    Thruster_Tests();
    ~Thruster_Tests();

private slots:
    void SetThrust_ToAnyValue_SetsThrust();
    void Save_CreatesNewFile();
    void Load_LoadsIntegrityValue();
};

Thruster_Tests::Thruster_Tests() {}

Thruster_Tests::~Thruster_Tests() {}

void Thruster_Tests::SetThrust_ToAnyValue_SetsThrust() {
    // Arrange
    Thruster thruster = Thruster();
    float expectedValue = 1.f;

    // Act
    thruster.SetThrust(1.f);

    // Assert
    QCOMPARE(thruster.GetThrust(), expectedValue);
}

void Thruster_Tests::Save_CreatesNewFile() {
    // Arrange
    Thruster thruster = Thruster();

    // Act
    thruster.Save("thruster.txt");

    // Assert
    QVERIFY(QFileInfo::exists("thruster.txt"));

    // Cleanup
    if (QFileInfo::exists("thruster.txt")) {
        QFile::remove("thruster.txt");
    }
}

void Thruster_Tests::Load_LoadsIntegrityValue() {
    // Arrange
    Thruster thruster = Thruster();
    float expectedValue = -1.f;
    thruster.SetThrust(-1.f);
    thruster.Save("thruster.txt");
    thruster.SetThrust(0.f);

    // Act
    thruster.Load("thruster.txt");

    // Assert
    QCOMPARE(thruster.GetThrust(), expectedValue);

    // Cleanup
    if (QFileInfo::exists("thruster.txt")) {
        QFile::remove("thruster.txt");
    }
}

QTEST_APPLESS_MAIN(Thruster_Tests)

#include "tst_thruster_tests.moc"
