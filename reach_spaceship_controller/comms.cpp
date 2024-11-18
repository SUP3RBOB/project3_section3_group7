#include "comms.h"
#include <QFile>
#include <QTextStream>
#include <QVariant>

using namespace Qt;

Communication::Communication() : QObject() {
    messagesToReceive = QList<QString>({
        "Congratulations on completing the latest mission objective!",
        "Flight path remains optimal, no debris warnings at this time.",
        "Ground team reports all personnel shifts are covered through the week.",
        "Earth visuals report clear skies over major continents.",
        "Mission status remains nominal, no deviations to report.",
        "All satellite uplinks functioning at full capacity.",
        "Meteor shower expected to pass within safe distance.",
        "Ground-based system test conducted without discrepancies.",
        "Message from your family uploaded: 'We miss you!'",
        "Visual inspection of solar panels indicated no irregularities.",
        "Scientists discover new Earth-like planet 1000 light years away!",
        "Congratulations on meeting research milestone goals.",
        "Zero-G training footage review available upon request.",
        "Update: No changes in the Earth's magnetic field affecting operations.",
        "Ground-based weather radar confirms no storm development affecting re-entry zones.",
        "All external camera feeds operational and transmitting correctly.",
        "Routine waste management check successful.",
        "Optical lens cleaning protocol completed by system.",
        "Heat shielding status report: no irregularities detected.",
        "Astronomical research data shared from observatories worldwide"
    });

    MessagesReceived = QList<QString>();
    receiveMessages = true;
}

void Communication::ReceiveRandomMessage() {
    if (receiveMessages && !messagesToReceive.empty()) {
        int num = rand() % messagesToReceive.count();
        QString message = QString(messagesToReceive[num]);

        MessagesReceived.push_back(message);
        emit OnMessageReceived(message);
        messagesToReceive.removeAt(num);
    }
}

bool Communication::CanReceiveMessages() {
    return receiveMessages;
}

void Communication::ToggleReceiveMessages() {
    receiveMessages = !receiveMessages;
}

void Communication::Save(QString fileName) {
    QFile file = QFile(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream stream = QTextStream(&file);
    stream << receiveMessages << endl;

    if (MessagesReceived.count() <= 0) {
        file.close();
        return;
    }

    for (QString& message : MessagesReceived) {
        stream << message << endl;
    }

    file.close();
}

void Communication::Load(QString fileName) {
    QFile file = QFile(fileName);
    bool success = file.open(QIODevice::ReadOnly);

    if (!success) {
        return;
    }

    QTextStream stream = QTextStream(&file);
    receiveMessages = QVariant(stream.readLine()).toBool();
    while (!stream.atEnd()) {
        QString message = stream.readLine();
        messagesToReceive.removeOne(message);
        MessagesReceived.push_back(message);
    }

    file.close();
}

Communication::~Communication() { }
