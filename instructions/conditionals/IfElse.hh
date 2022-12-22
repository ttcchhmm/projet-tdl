#pragma once

#include "../../Utils.hh"
#include "../Instruction.hh"

/**
 * @brief The 'if/else' conditional.
 */
class IfElse: public Instruction {
    private:
        /**
         * @brief The condition.
         */
        std::shared_ptr<Instruction> _cond;

        /**
         * @brief The instructions to run if true.
         */
        InstructionList _instructionsTrue;

        /**
         * @brief The instructions to run if false.
         */
        InstructionList _instructionsFalse;

    public:
        /**
         * @brief Construct a new IfElse instruction.
         * @param cond The condition.
         * @param ifTrue The instructions to run if the condition is true.
         * @param ifFalse The instructions to run if the condition is false.
         */
        IfElse(std::shared_ptr<Instruction> cond, InstructionList const & ifTrue, InstructionList const & ifFalse);
        IfElse(IfElse const &) = default;
        ~IfElse() override = default;

        bool execute(Field garden) override;
};