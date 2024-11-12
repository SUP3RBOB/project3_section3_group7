#include <QtTest>
#include "navigation.h"

// add necessary includes here

class Navigation_tests : public QObject {
    Q_OBJECT

    void ClearFiles();

public:
    Navigation_tests();
    ~Navigation_tests();

private slots:
    void ApplyThrust_ModifiesThrustDirection();
    void ApplyThrust_ModifiesThrustVelocity();
    void Save_CreatesNewFiles();
    void Load_LoadsNavigationValues();
    void Load_LoadsThrusterValues();
};

Navigation_tests::Navigation_tests() {}

Navigation_tests::~Navigation_tests() {}

void Navigation_tests::ClearFiles() {
    if (QFileInfo::exists("navigation.txt")) {
        QFile::remove("navigation.txt");
    }

    if (QFileInfo::exists("thrusterx.txt")) {
        QFile::remove("thrusterx.txt");
    }

    if (QFileInfo::exists("thrustery.txt")) {
        QFile::remove("thrustery.txt");
    }
}

void Navigation_tests::ApplyThrust_ModifiesThrustDirection() {
    // Arrange
    Navigation nav = Navigation();
    nav.ThrusterX().SetThrust(-1.f);
    nav.ThrusterY().SetThrust(1.f);
    QVector2D expectedDirection = QVector2D(-1.f, 1.f);

    // Act
    nav.ApplyThrust(1000.f, 0.016f);

    // Assert
    QCOMPARE(nav.Direction, expectedDirection);
}

void Navigation_tests::ApplyThrust_ModifiesThrustVelocity() {
    // Arrange
    Navigation nav = Navigation();
    nav.ThrusterX().SetThrust(-1.f);
    nav.ThrusterY().SetThrust(1.f);
    QVector2D expectedVelocity = QVector2D(-0.08f, 0.08f);

    // Act
    nav.ApplyThrust(1000.f, 0.016f);

    // Assert
    QVERIFY(qFuzzyCompare(nav.Velocity.x(), expectedVelocity.x()));
    QVERIFY(qFuzzyCompare(nav.Velocity.y(), expectedVelocity.y()));
}

void Navigation_tests::Save_CreatesNewFiles() {
    // Arrange
    Navigation nav = Navigation();

    // Act
    nav.Save("navigation.txt");

    // Assert
    QVERIFY(QFileInfo::exists("navigation.txt"));
    QVERIFY(QFileInfo::exists("thrusterx.txt"));
    QVERIFY(QFileInfo::exists("thrustery.txt"));

    // Cleanup
    ClearFiles();
}

void Navigation_tests::Load_LoadsNavigationValues() {
    // Arrange
    Navigation nav = Navigation();
    nav.Position = QVector2D(1.f, 1.f);
    nav.Direction = QVector2D(2.f, 2.f);
    nav.Velocity = QVector2D(3.f, 3.f);
    nav.Acceleration = QVector2D(4.f, 4.f);
    nav.Save("navigation.txt");
    nav.Position = QVector2D();
    nav.Direction = QVector2D();
    nav.Velocity = QVector2D();
    nav.Acceleration = QVector2D();
    QVector2D expectedPosition = QVector2D(1.f, 1.f);
    QVector2D expectedDirection = QVector2D(2.f, 2.f);
    QVector2D expectedVelocity = QVector2D(3.f, 3.f);
    QVector2D expectedAcceleration = QVector2D(4.f, 4.f);

    // Act
    nav.Load("navigation.txt");

    // Assert
    QCOMPARE(nav.Position, expectedPosition);
    QCOMPARE(nav.Direction, expectedDirection);
    QCOMPARE(nav.Velocity, expectedVelocity);
    QCOMPARE(nav.Acceleration, expectedAcceleration);

    // Cleanup
    ClearFiles();
}

void Navigation_tests::Load_LoadsThrusterValues() {
    // Arrange
    Navigation nav = Navigation();
    nav.ThrusterX().SetThrust(-1.f);
    nav.ThrusterY().SetThrust(1.f);
    nav.Save("navigation.txt");
    nav.ThrusterX().SetThrust(0.f);
    nav.ThrusterY().SetThrust(0.f);
    float expectedThrustX = -1.f;
    float expectedThrustY = 1.f;

    // Act
    nav.Load("navigation.txt");

    // Assert
    QCOMPARE(nav.ThrusterX().GetThrust(), expectedThrustX);
    QCOMPARE(nav.ThrusterY().GetThrust(), expectedThrustY);

    // Cleanup
    ClearFiles();
}

QTEST_APPLESS_MAIN(Navigation_tests)

#include "tst_navigation_tests.moc"
