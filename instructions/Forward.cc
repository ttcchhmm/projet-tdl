#include "Forward.hh"

#include <iostream>

Forward::Forward(std::size_t turtle, int amount): Instruction(turtle), _amount(amount) {}

bool Forward::execute(Field garden) {
    if(!Instruction::execute(garden)) {
        return false;
    }

    float orientation = garden->orientation(getTarget());
    int x = garden->position(getTarget()).x();
    int y = garden->position(getTarget()).y();

    if(orientation == 0) {
        if(garden->estVide(x, y - _amount)) {
            garden->changePosition(getTarget(), x, y - _amount);
        } else {
            displayErrorMessage();
            return false;
        }
    } else if(orientation == 90) {
        if(garden->estVide(x + _amount, y)) {
            garden->changePosition(getTarget(), x + _amount, y);
        } else {
            displayErrorMessage();
            return false;
        }
    } else if(orientation == 180) {
        if(garden->estVide(x, y + _amount)) {
            garden->changePosition(getTarget(), x, y + _amount);
        } else {
            displayErrorMessage();
            return false;
        }
    } else if(orientation == 270) {
        if(garden->estVide(x - _amount, y)) {
            garden->changePosition(getTarget(), x - _amount, y);
        } else {
            displayErrorMessage();
            return false;
        }
    }

    return true;
}

void Forward::displayErrorMessage() const {
    std::cerr << "Failed to move the turtle with ID " << getTarget() << "." << std::endl;
}