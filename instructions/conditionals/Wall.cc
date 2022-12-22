#include "Wall.hh"

Wall::Wall(std::size_t turtle, CheckDirection const & dir): Empty(turtle, dir) {}

bool Wall::execute(JardinRendering* const & garden) {
    return !Empty::execute(garden);
}