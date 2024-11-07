#include <QtTest>

#include "hull.h"

class Hull_Tests : public QObject {
    Q_OBJECT

public:
    Hull_Tests();
    ~Hull_Tests();

private slots:
    void SetHullIntegrity_WithProperValue_SetsIntegrity();
    void SetHullIntegrity_WithNegativeValue_ClampsIntegrityTo0();
    void SetHullIntegrity_WithValueOver100_ClampsIntegrityTo100();
    void Save_CreatesNewFile();
    void Load_LoadsIntegrityValue();
};

Hull_Tests::Hull_Tests() {}

Hull_Tests::~Hull_Tests() {}

void Hull_Tests::SetHullIntegrity_WithProperValue_SetsIntegrity() {
    // Arrange
    Hull hull = Hull();
    float expectedValue = 65.5f;

    // Act
    hull.SetIntegrity(65.5f);

    // Assert
    QCOMPARE(hull.GetIntegrity(), expectedValue);
}

void Hull_Tests::SetHullIntegrity_WithNegativeValue_ClampsIntegrityTo0() {
    // Arrange
    Hull hull = Hull();
    float expectedValue = 0.f;

    // Act
    hull.SetIntegrity(-55.4f);

    // Assert
    QCOMPARE(hull.GetIntegrity(), expectedValue);
}

void Hull_Tests::SetHullIntegrity_WithValueOver100_ClampsIntegrityTo100() {
    // Arrange
    Hull hull = Hull();
    float expectedValue = 100.f;

    // Act
    hull.SetIntegrity(112.f);

    // Assert
    QCOMPARE(hull.GetIntegrity(), expectedValue);
}

void Hull_Tests::Save_CreatesNewFile() {
    // Arrange
    Hull hull = Hull();

    // Act
    hull.Save("hull.txt");

    // Assert
    QVERIFY(QFileInfo::exists("hull.txt"));

    // Cleanup
    if (QFileInfo::exists("hull.txt")) {
        QFile::remove("hull.txt");
    }
}

void Hull_Tests::Load_LoadsIntegrityValue() {
    // Arrange
    Hull hull = Hull();
    float expectedValue = 55.5f;
    hull.SetIntegrity(55.5f);
    hull.Save("hull.txt");
    hull.SetIntegrity(0.f);

    // Act
    hull.Load("hull.txt");

    // Assert
    QCOMPARE(hull.GetIntegrity(), expectedValue);

    // Cleanup
    if (QFileInfo::exists("hull.txt")) {
        QFile::remove("hull.txt");
    }
}

QTEST_APPLESS_MAIN(Hull_Tests)

#include "tst_hull_tests.moc"
