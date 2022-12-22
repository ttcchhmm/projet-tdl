#pragma once

#include "../../Utils.hh"
#include "../Instruction.hh"

/**
 * @brief The 'repeat' loop.
 */
class Repeat: public Instruction {
    private:
        /**
         * @brief The amount of times the loop will be repeated.
         */
        unsigned int _amount;

        /**
         * @brief The instructions to run.
         */
        InstructionList _instructions;

    public:
        /**
         * @brief Construct a new repeat instruction.
         * @param amount The amount of times the instructions will be looped.
         * @param instructions The instructions to loop.
         */
        Repeat(unsigned int amount, InstructionList instructions);
        Repeat(Repeat const &) = default;
        ~Repeat() = default;

        bool execute(Field garden) override;
};