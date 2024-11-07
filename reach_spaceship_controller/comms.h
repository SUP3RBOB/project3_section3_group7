#ifndef COMMS_H
#define COMMS_H

#include <QObject>
#include <QList>
#include "isavable.h"

/// The communication module of the spaceship.
class Communication : public QObject, public ISavable {
private:
    Q_OBJECT

    bool receiveMessages;
    QList<QString> messagesToReceive;

public:
    /// Creates a new communication class.
    Communication();

    ~Communication();

    /// Messages that have been received.
    QList<QString> MessagesReceived;

    /// Receive a random communication message.
    void ReceiveRandomMessage();

    /// Whether the comms can receive messages or not.
    bool CanReceiveMessages();

    /// Enable.disable the ability to receive messages.
    void ToggleReceiveMessages();

    /// Saves received messages to a file.
    virtual void Save(QString fileName) override;

    /// Loads messages from a file into the list of received messages.
    virtual void Load(QString fileName) override;

signals:

    /// Invoked when a new message is received.
    void OnMessageReceived(QString message);
};

#endif // COMMS_H
