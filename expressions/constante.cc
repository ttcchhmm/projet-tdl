#include "constante.hh"

Constante::Constante(double valeur) : _valeur(valeur) {}

double Constante::calculer(const Contexte &) const {
    return _valeur;
}
