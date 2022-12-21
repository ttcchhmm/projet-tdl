#pragma once

#include "Instruction.hh"

#include <string>

/**
 * @brief An instruction that loads a new garden.
 */
class Garden: public Instruction {
    private:
        /**
         * @brief The path of the garden file.
         */
        std::string _filename;

    public:
        /**
         * @brief Construct a new Garden instruction.
         * 
         * @param filename The path to the garden file.
         */
        Garden(std::string const & filename);
        Garden(Garden const &) = default;
        ~Garden() override = default;

        bool execute(JardinRendering* const & garden) override;
};