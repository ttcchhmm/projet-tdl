#include "Forward.hh"

unsigned int Forward::numberOfArguments() const {
    return 1;
}

bool Forward::execute(JardinRendering* const & garden, std::size_t const & target, std::vector<int> const & args) {
    float orientation = garden->orientation(target);
    int x = garden->position(target).x();
    int y = garden->position(target).y();

    std::cout << orientation << " | " << x << "/" << y << std::endl;

    if(orientation == 0) {
        garden->changePosition(target, x, y - args[0]);
    } else if(orientation == 90) {
        garden->changePosition(target, x + args[0], y);
    } else if(orientation == 180) {
        garden->changePosition(target, x, y + args[0]);
    } else if(orientation == 270) {
        garden->changePosition(target, x - args[0], y);
    }

    return true;
}