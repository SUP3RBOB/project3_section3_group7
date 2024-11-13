#include <QtTest>
#include "spaceship.h"

class Spaceship_Tests : public QObject {
    Q_OBJECT
private:
    bool FilesExist();
    void DeleteFiles();

public:
    Spaceship_Tests();
    ~Spaceship_Tests();

private slots:
    void Save_SavesAllModulesToTheirOwnFile();
};

Spaceship_Tests::Spaceship_Tests() {}

Spaceship_Tests::~Spaceship_Tests() {}

void Spaceship_Tests::Save_SavesAllModulesToTheirOwnFile() {
    // Arrange
    Spaceship spaceship = Spaceship();

    // Act
    spaceship.Save();

    // Assert
    QVERIFY(FilesExist());

    // Cleanup
    DeleteFiles();
}

bool Spaceship_Tests::FilesExist() {
    return QFile::exists("navigation.txt") &&
        QFile::exists("power.txt") &&
        QFile::exists("lights.txt") &&
        QFile::exists("comms.txt") &&
        QFile::exists("lifesupport.txt") &&
        QFile::exists("hull.txt");
}

void Spaceship_Tests::DeleteFiles() {
    if (QFile::exists("navigation.txt")) {
        QFile::remove("navigation.txt");
    }

    if (QFile::exists("power.txt")) {
        QFile::remove("power.txt");
    }

    if (QFile::exists("lights.txt")) {
        QFile::remove("lights.txt");
    }

    if (QFile::exists("comms.txt")) {
        QFile::remove("comms.txt");
    }

    if (QFile::exists("lifesupport.txt")) {
        QFile::remove("lifesupport.txt");
    }

    if (QFile::exists("hull.txt")) {
        QFile::remove("hull.txt");
    }
}

QTEST_APPLESS_MAIN(Spaceship_Tests)

#include "tst_spaceship_tests.moc"
