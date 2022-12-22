#include "Garden.hh"

#include <fstream>
#include <iostream>

Garden::Garden(std::string const & filename): Instruction(0), _filename(filename) {}

bool Garden::execute(Field garden) {
    garden->nettoyerJardin();

    std::ifstream is(_filename);
    std::string line;
    unsigned int posY(0);
    while(getline(is, line)) {
        unsigned int posX(0);
        for(auto const & chr : line) {
            if(chr == '_') { // Empty space
                garden->ajouterVide(posX, posY);
            } else if(chr == '*') { // Wall
                garden->ajouterMur(posX, posY);
            } else if(chr == 'T') { // Turtle
                garden->ajouterVide(posX, posY);
                garden->nouvelleTortue();
                garden->changePosition(garden->getTortues().size() - 1, posX, posY);
            } else { // Malformed garden
                std::cerr << "Invalid garden file." << std::endl;
                return false;
            }

            posX++;
        }

        posY++;
    }

    is.close();

    return true;
}