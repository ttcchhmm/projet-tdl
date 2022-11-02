#ifndef DRIVER_H
#define DRIVER_H

#include <map>
#include <string>
#include <QPoint>
#include <QColor>
#include <QSize>
#include "contexte.hh"

class JardinRendering;

class Driver {
private:      
    JardinRendering * monJardin;
    Contexte variables;       

public:
 Driver(JardinRendering * J);
    ~Driver();
    const   Contexte& getContexte() const;
    double  getVariable(const std::string& name) const;
    void    setVariable(const std::string& name, double value);
/* EXEMPLE
    void    Driver::changerPositionTortue0(int x, int y);
    float    obtenirOrientationTortue1();
*/ 

};

#endif


