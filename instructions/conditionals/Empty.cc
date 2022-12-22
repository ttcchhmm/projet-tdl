#include "Empty.hh"

Empty::Empty(std::size_t turtle, CheckDirection const & dir): Instruction(turtle), _direction(dir) {}

bool Empty::execute(Field garden) {
    if(!Instruction::execute(garden)) {
        return false;
    }

    float delta(0);

    switch(_direction) {
        case CheckDirection::FRONT: {
            delta = 0;
            break;
        }

        case CheckDirection::RIGHT: {
            delta = 90;
            break;
        }

        case CheckDirection::BACK: {
            delta = 180;
            break;
        }

        case CheckDirection::LEFT: {
            delta = 270;
            break;
        }

        default: { // Shouldn't happen
            delta = 0;
            break;
        }
    }

    float orientation(garden->orientation(getTarget()) + delta);

    // Stay in bounds
    if(orientation > 360) {
        orientation -= 360;
    } else if(orientation < 0) {
        orientation += 360;
    }

    if(orientation == 0) {
        return !garden->estMur(garden->getTortues()[getTarget()]->getX(), garden->getTortues()[getTarget()]->getY() - 1);
    } else if(orientation == 90) {
        return !garden->estMur(garden->getTortues()[getTarget()]->getX() + 1, garden->getTortues()[getTarget()]->getY());
    } else if(orientation == 180) {
        return !garden->estMur(garden->getTortues()[getTarget()]->getX(), garden->getTortues()[getTarget()]->getY() + 1);
    } else if(orientation == 270) {
        return !garden->estMur(garden->getTortues()[getTarget()]->getX() - 1, garden->getTortues()[getTarget()]->getY());
    }

    return false;
}