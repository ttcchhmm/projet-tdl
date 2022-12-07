#include "Forward.hh"

Forward::Forward(std::size_t turtle, int amount): Instruction(turtle), _amount(amount) {}

bool Forward::execute(JardinRendering* const & garden) {
    float orientation = garden->orientation(getTarget());
    int x = garden->position(getTarget()).x();
    int y = garden->position(getTarget()).y();

    std::cout << orientation << " | " << x << "/" << y << std::endl;

    if(orientation == 0) {
        garden->changePosition(getTarget(), x, y - _amount);
    } else if(orientation == 90) {
        garden->changePosition(getTarget(), x + _amount, y);
    } else if(orientation == 180) {
        garden->changePosition(getTarget(), x, y + _amount);
    } else if(orientation == 270) {
        garden->changePosition(getTarget(), x - _amount, y);
    }

    return true;
}