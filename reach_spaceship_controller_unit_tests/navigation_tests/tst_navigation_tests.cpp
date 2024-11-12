#include <QtTest>
#include "navigation.h"

// add necessary includes here

class Navigation_tests : public QObject {
    Q_OBJECT

public:
    Navigation_tests();
    ~Navigation_tests();

private slots:
    void Save_CreatesNewFile();
    void Load_LoadsNavigationValues();
};

Navigation_tests::Navigation_tests() {}

Navigation_tests::~Navigation_tests() {}

void Navigation_tests::Save_CreatesNewFile() {
    // Arrange
    Navigation nav = Navigation();

    // Act
    nav.Save("navigation.txt");

    // Assert
    QVERIFY(QFileInfo::exists("navigation.txt"));

    // Cleanup
    if (QFileInfo::exists("navigation.txt")) {
        QFile::remove("navigation.txt");
    }
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
    if (QFileInfo::exists("navigation.txt")) {
        QFile::remove("navigation.txt");
    }
}

QTEST_APPLESS_MAIN(Navigation_tests)

#include "tst_navigation_tests.moc"
