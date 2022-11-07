#include "driver.hh"
#include "jardinHandler.hh"
#include <iostream>

Driver::Driver(JardinHandler * J) {
    monJardin = J;
}

Driver::~Driver() {
	delete monJardin;
}

const Contexte& Driver::getContexte() const {
    return variables;
}

double Driver::getVariable(const std::string & name) const {
    return variables.get(name);
}

void Driver::setVariable(const std::string & name, double value) {
    variables[name] = value;
}

JardinRendering * Driver::getJardin() {
    return monJardin->getJardinRendering();
}

/* EXEMPLE
void    Driver::changerPositionTortue0(int x, int y) {
    monJardin->changePosition(0,x,y);
}

float    Driver::obtenirOrientationTortue1() {
    monJardin->orientation(1,o);
}
/*/
