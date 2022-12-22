#include "Rotate.hh"

Rotate::Rotate(std::size_t turtle, directions dir, unsigned int amount): Instruction(turtle), _dir(dir), _amount(amount) {}

bool Rotate::execute(JardinRendering* const & garden) {
    if(!Instruction::execute(garden)) {
        return false;
    }

    float newOrientation = garden->orientation(getTarget());
    switch(_dir) {
        case directions::LEFT: {
            for(unsigned int i(0); i < _amount; i++) {
                newOrientation -= 90;

                if(newOrientation < 0) {
                    newOrientation += 360;
                }
            }

            break;
        }

        case directions::RIGHT: {
            for(unsigned int i(0); i < _amount; i++) {
                newOrientation += 90;

                if(newOrientation > 360) {
                    newOrientation -= 360;
                }
            }

            break;
        }
    }

    garden->changeOrientation(getTarget(), newOrientation);
    
    return true;
}