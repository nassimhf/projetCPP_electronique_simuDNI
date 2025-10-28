// InputData.cpp
#include "pch.h"
#include "InputData.h"

InputData::InputData() {
    // Initialiser avec un seul point par défaut
    inputs.push_back(InputPoint(0, 0, 0));
}

void InputData::addInput(int x, int y, int z) {
    inputs.push_back(InputPoint(x, y, z));
}

void InputData::addInput(InputPoint point) {
    inputs.push_back(point);
}

vector<InputPoint> InputData::getInputs() const {
    return inputs;
}

InputPoint InputData::getInput(int index) const {
    if (index >= 0 && index < inputs.size()) {
        return inputs[index];
    }
    return InputPoint(0, 0, 0);
}

int InputData::size() const {
    return inputs.size();
}

void InputData::clear() {
    inputs.clear();
}