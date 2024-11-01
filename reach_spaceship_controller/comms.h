#ifndef COMMS_H
#define COMMS_H

#include <QObject>
#include <QList>

class Communication : public QObject {
private:
    Q_OBJECT

    bool receiveMessages;
    QList<QString> messagesToReceive;

public:
    // Creates a new communication class
    Communication();

    void ReceiveRandomMessage();
    bool CanReceiveMessages();
    void ToggleReceiveMessages();

signals:

    /// Invoked when a new message is received.
    void MessageReceived(QString message);
};

#endif // COMMS_H
