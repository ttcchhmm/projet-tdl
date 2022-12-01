#include "Rotate.hh"

unsigned int Rotate::numberOfArguments() const {
    return 1;
}

bool Rotate::execute(JardinRendering* const & garden, std::size_t const & target, std::vector<directions> const & args) {
    float newOrientation = garden->orientation(target);
    switch(args[0]) {
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

    garden->changeOrientation(target, newOrientation);
    
    return true;
}