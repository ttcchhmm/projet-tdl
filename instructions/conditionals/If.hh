#pragma once

#include "../../Utils.hh"
#include "../Instruction.hh"

/**
 * @brief The 'if' conditional.
 */
class If: public Instruction {
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
         * @brief Construct a new If instruction.
         * @param cond The condition.
         * @param instructions The instructions if the condition is true.
         */
        If(std::shared_ptr<Instruction> cond, InstructionList const & instructions);
        If(If const &) = default;
        ~If() override = default;

        bool execute(JardinRendering* const & garden) override;
};