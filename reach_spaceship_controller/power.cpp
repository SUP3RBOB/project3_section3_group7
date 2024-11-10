#include "power.h"
#include <QFile>
#include <QTextStream>

// Constructor for Power class
// Initializes the power level to the specified initialPower and sets
// the on/off status to false (off) by default.
Power::Power(float initialPower) : power(initialPower), on(false) {}

// Returns the current power level.
float Power::GetPower() const {
    return power;
}

// Returns true if the power is on, false otherwise.
bool Power::IsOn() const {
    return on;
}

// Sets the power level to the specified value.
void Power::SetPower(float level) {
    power = level;
}

// Sets the power on/off status to the specified value (true for on, false for off).
void Power::SetOn(bool status) {
    on = status;
}

// Saves the current state of the Power module (on/off status and power level) to a file.
// The file is saved in text format with two lines:
// 1. Power status (1 for on, 0 for off)
// 2. Power level as a float
void Power::Save(QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << on << "\n" << power << "\n"; // Write on/off status and power level
        file.close();
    }
}

// Loads the state of the Power module from a file.
// Expects the file to have two lines:
// 1. Power status (1 for on, 0 for off)
// 2. Power level as a float
void Power::Load(QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int status;
        in >> status >> power;            // Read on/off status and power level
        on = static_cast<bool>(status);   // Convert integer status to boolean
        file.close();
    }
}
