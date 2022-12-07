#include "Rotate.hh"

Rotate::Rotate(std::size_t turtle, directions dir): Instruction(turtle), _dir(dir) {}

bool Rotate::execute(JardinRendering* const & garden) {
    float newOrientation = garden->orientation(getTarget());
    switch(_dir) {
        case directions::LEFT: {
            newOrientation -= 90;

            if(newOrientation < 0) {
                newOrientation += 360;
            }

            break;
        }

        case directions::RIGHT: {
            newOrientation += 90;

            if(newOrientation > 360) {
                newOrientation -= 360;
            }

            break;
        }
    }

    garden->changeOrientation(getTarget(), newOrientation);
    
    return true;
}