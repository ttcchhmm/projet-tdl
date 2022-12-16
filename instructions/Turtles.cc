#include "Turtles.hh"

Turtles::Turtles(unsigned int nbTurtles): Instruction(0), _nbTurtles(nbTurtles) {}

bool Turtles::execute(JardinRendering* const & garden) {
    // Check for non default number of turtles.
    if(garden->nombreTortues() != 1) {
        std::cerr << "Non default number of turtles already set." << std::endl;
        return false;
    }

    // Spawn turtles.
    while(garden->nombreTortues() != _nbTurtles) {
        garden->nouvelleTortue();
    }

    return true;
}