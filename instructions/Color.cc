#include "Color.hh"

#include <QString>
#include <iostream>

Color::Color(std::size_t _turtle, ColorZone const & zone, std::string const & colorHexa): Instruction(_turtle), _zone(zone), _colorHexa(colorHexa) {}

bool Color::execute(Field garden) {
    if(!Instruction::execute(garden)) {
        return false;
    }

    auto r(QString::fromStdString(_colorHexa.substr(0, 2)).toInt(nullptr, 16));
    auto g(QString::fromStdString(_colorHexa.substr(2, 2)).toInt(nullptr, 16));
    auto b(QString::fromStdString(_colorHexa.substr(4, 2)).toInt(nullptr, 16));

    switch(_zone) {
        case ColorZone::PATTERN: {
            garden->changeCouleurMotif(getTarget(), r, g, b);
            break;
        }

        default:
        case ColorZone::SHELL: {
            garden->changeCouleurCarapace(getTarget(), r, g, b);
            break;
        }
    }

    return true;
}