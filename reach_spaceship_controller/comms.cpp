#include "comms.h"

Communication::Communication() : QObject() {
    messagesToReceive = QList<QString>(
        "Congratulations on completing the latest mission objective!"
    );
}

void Communication::ReceiveRandomMessage() {
    if (receiveMessages && !messagesToReceive.empty()) {
        int num = rand() % messagesToReceive.count();

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
