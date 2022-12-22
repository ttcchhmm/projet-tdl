#include "Jump.hh"

Jump::Jump(std::size_t turtle, unsigned int amount): Instruction(turtle), _amount(amount) {}

bool Jump::execute(Field garden) {
    if(!Instruction::execute(garden)) {
        return false;
    }

    for(unsigned int i(0); i < _amount; i++) {
        float orientation = garden->orientation(getTarget());
        int x = garden->position(getTarget()).x();
        int y = garden->position(getTarget()).y();

        if(orientation == 0) {
            if(garden->estVide(x, y - 2)) {
                garden->changePosition(getTarget(), x, y - 2);
            } else {
                displayErrorMessage();
                return false;
            }
        } else if(orientation == 90) {
            if(garden->estVide(x + 2, y)) {
                garden->changePosition(getTarget(), x + 2, y);
            } else {
                displayErrorMessage();
                return false;
            }
        } else if(orientation == 180) {
            if(garden->estVide(x, y + 2)) {
                garden->changePosition(getTarget(), x, y + 2);
            } else {
                displayErrorMessage();
                return false;
            }
        } else if(orientation == 270) {
            if(garden->estVide(x - 2, y)) {
                garden->changePosition(getTarget(), x - 2, y);
            } else {
                displayErrorMessage();
                return false;
            }
        }
    }

    return true;
}

void Jump::displayErrorMessage() const {
    std::cerr << "Failed to jump the turtle with ID " << getTarget() << "." << std::endl;
}