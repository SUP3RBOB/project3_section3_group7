#include <QtTest>
#include "simulation.h"

class Simulation_Tests : public QObject {
    Q_OBJECT

    bool VectorFuzzyCompare(const QVector2D& v1, const QVector2D& v2);

public:
    Simulation_Tests();
    ~Simulation_Tests();

private slots:
    void Update_UpdatesSpaceshipOrbitalPosition();
    void Update_UpdatesSpaceshipOrbitalVelocity();
    void Update_UpdatesSpaceshipOrbitalAcceleration();
};

bool Simulation_Tests::VectorFuzzyCompare(const QVector2D& v1, const QVector2D& v2) {
    return qFuzzyCompare(v1.x(), v2.x()) && qFuzzyCompare(v1.y(), v2.y());
}

Simulation_Tests::Simulation_Tests() {}

Simulation_Tests::~Simulation_Tests() {}

void Simulation_Tests::Update_UpdatesSpaceshipOrbitalPosition() {
    // Arrange
    Simulation simulation = Simulation();
    QVector2D expectedPosition = QVector2D(122.72f, 7.371e+06f);

    // Act
    simulation.Update(0.016f, 1.f);

    // Assert
    Navigation& nav = simulation.GetSpaceship().GetNavigation();
    QVERIFY(VectorFuzzyCompare(nav.Position, expectedPosition));
}

void Simulation_Tests::Update_UpdatesSpaceshipOrbitalVelocity() {
    // Arrange
    Simulation simulation = Simulation();
    QVector2D expectedVelocity = QVector2D(7670.f, -0.11738f);

    // Act
    simulation.Update(0.016f, 1.f);

    // Assert
    Navigation& nav = simulation.GetSpaceship().GetNavigation();
    QVERIFY(VectorFuzzyCompare(nav.Velocity, expectedVelocity));
}

void Simulation_Tests::Update_UpdatesSpaceshipOrbitalAcceleration() {
    // Arrange
    Simulation simulation = Simulation();
    QVector2D expectedAcceleration = QVector2D(0.f, -7.33623f);

    // Act
    simulation.Update(0.016f, 1.f);

    // Assert
    Navigation& nav = simulation.GetSpaceship().GetNavigation();
    QVERIFY(VectorFuzzyCompare(nav.Acceleration, expectedAcceleration));
}

QTEST_APPLESS_MAIN(Simulation_Tests)

#include "tst_simulation_tests.moc"
