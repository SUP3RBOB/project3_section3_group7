#include <QtTest>
#include "comms.h"

class Comms_Tests : public QObject {
    Q_OBJECT
private:
    QString emittedMessage = "Blank Message";
    void OnReceivedMessage(QString message);

public:
    Comms_Tests();
    ~Comms_Tests();

private slots:
    void ReceiveRandomMessage_AddsMessageToReceivedList();
    void ReceiveRandomMessage_EmitsMessageReceivedSignal();
    void ToggleReceiveMessages_AsFalse_EnablesReceiveMessages();
    void ToggleReceiveMessages_AsTrue_DisablesReceiveMessages();
    void Save_CreatesNewFile();
    void Load_LoadsMessagesIntoList();
};

Comms_Tests::Comms_Tests() {}

Comms_Tests::~Comms_Tests() {}

void Comms_Tests::ReceiveRandomMessage_AddsMessageToReceivedList() {
    // Arrange
    Communication comms = Communication();

    // Act
    comms.ReceiveRandomMessage();

    // Assert
    QVERIFY(comms.MessagesReceived.count() > 0);
}

void Comms_Tests::ReceiveRandomMessage_EmitsMessageReceivedSignal() {
    // Arrange
    Communication comms = Communication();
    connect(&comms, &Communication::MessageReceived, this, &Comms_Tests::OnReceivedMessage);

    // Act
    comms.ReceiveRandomMessage();

    // Assert
    QVERIFY(emittedMessage != "Blank Message");
}

void Comms_Tests::ToggleReceiveMessages_AsFalse_EnablesReceiveMessages() {
    // Arrange
    Communication comms = Communication();

    // Act
    comms.ToggleReceiveMessages();

    // Assert
    QVERIFY(comms.CanReceiveMessages());
}

void Comms_Tests::ToggleReceiveMessages_AsTrue_DisablesReceiveMessages() {
    // Arrange
    Communication comms = Communication();
    if (!comms.CanReceiveMessages()) {
        comms.ToggleReceiveMessages();
    }

    // Act
    comms.ToggleReceiveMessages();

    // Assert
    QVERIFY(!comms.CanReceiveMessages());
}

void Comms_Tests::Save_CreatesNewFile() {
    // Arrange
    Communication comms = Communication();

    // Act
    comms.Save("comms.txt");

    // Assert
    QVERIFY(QFileInfo::exists("comms.txt"));

    // Cleanup
    if (QFileInfo::exists("comms.txt")) {
        QFile::remove("comms.txt");
    }
}

void Comms_Tests::Load_LoadsMessagesIntoList() {
    // Arrange
    Communication comms = Communication();
    comms.MessagesReceived.push_back("Random Message");
    comms.Save("comms.txt");
    comms.MessagesReceived.clear();

    // Act
    comms.Load("comms.txt");

    // Assert
    QVERIFY(comms.MessagesReceived.count() > 0);

    // Cleanup
    if (QFileInfo::exists("comms.txt")) {
        QFile::remove("comms.txt");
    }
}

void Comms_Tests::OnReceivedMessage(QString message) {
    emittedMessage = message;
}

QTEST_APPLESS_MAIN(Comms_Tests)

#include "tst_comms_tests.moc"
