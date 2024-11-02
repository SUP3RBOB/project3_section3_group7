#include "comms.h"
#include <QFile>
#include <QTextStream>

using namespace Qt;

Communication::Communication() : QObject() {
    messagesToReceive = QList<QString>(
        "Congratulations on completing the latest mission objective!"
    );
}

void Communication::ReceiveRandomMessage() {
    if (receiveMessages && !messagesToReceive.empty()) {
        int num = rand() % messagesToReceive.count();

        MessagesReceived.push_back(messagesToReceive[num]);
        emit MessageReceived(messagesToReceive[num]);
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
    if (MessagesReceived.count() <= 0) {
        return;
    }

    QFile file = QFile(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream stream = QTextStream(&file);
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
    while (!stream.atEnd()) {
        QString message = stream.readLine();
        messagesToReceive.removeOne(message);
        MessagesReceived.push_back(message);
    }

    file.close();
}
