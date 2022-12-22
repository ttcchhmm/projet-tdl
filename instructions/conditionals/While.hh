#pragma once

#include "../../Utils.hh"
#include "../Instruction.hh"

/**
 * @brief The 'while' loop.
 */
class While: public Instruction {
    private:
        /**
         * @brief The condition.
         */
        std::shared_ptr<Instruction> _cond;

        /**
         * @brief The instructions to run.
         */
        InstructionList _instructions;

    public:
        /**
         * @brief Construct a new While instruction.
         * @param cond The condition.
         * @param instructions The instructions if the condition is true.
         */
        While(std::shared_ptr<Instruction> cond, InstructionList instructions);
        While(While const &) = default;
        ~While() override = default;

        bool execute(Field garden) override;
};