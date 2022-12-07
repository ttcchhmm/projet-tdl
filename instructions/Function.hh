#pragma once

#include "Instruction.hh"

#include <list>
#include <string>

class Function {
    private:
        std::string _name;
        std::list<Instruction> _instructions;

    public:
        Function(std::string const & name);
        Function(Function const &) = default;
        ~Function() = default;

        /**
         * @brief Add an Instruction to this Function. 
         *
         * @param instruction The Instruction to add. 
         */
        void addInstruction(Instruction const & instruction);

        /**
         * @brief Execute the Function.
         * 
         * @param garden The garden to use as context.
         */
        void execute(JardinRendering* const & garden) const;

        [[nodiscard]] std::string getName() const;
};