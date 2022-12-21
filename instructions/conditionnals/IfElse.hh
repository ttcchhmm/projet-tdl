#pragma once

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
        std::list<std::shared_ptr<Instruction>> _instructionsTrue;

        /**
         * @brief The instructions to run if false.
         */
        std::list<std::shared_ptr<Instruction>> _instructionsFalse;

    public:
        /**
         * @brief Construct a new IfElse instruction.
         * @param cond The condition.
         * @param ifTrue The instructions to run if the condition is true.
         * @param ifFalse The instructions to run if the condition is false.
         */
        IfElse(std::shared_ptr<Instruction> cond, std::list<std::shared_ptr<Instruction>> const & ifTrue, std::list<std::shared_ptr<Instruction>> const & ifFalse);
        IfElse(IfElse const &) = default;
        ~IfElse() override = default;

        bool execute(JardinRendering* const & garden) override;
};