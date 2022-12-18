#pragma once

#include "Instruction.hh"
#include "Function.hh"

#include <memory>

/**
 * @brief Represent a function call.
 */
class FunctionCall: public Instruction {
    private:
        std::shared_ptr<Function> _function;
        std::vector<int> _args;

    public:
        /**
         * @brief Construct a new FunctionCall.
         * 
         * @param function The function to call.
         * @param args The arguments.
         */
        FunctionCall(std::shared_ptr<Function> function, std::vector<int> const & args);
        FunctionCall(FunctionCall const &) = default;
        ~FunctionCall() override = default;

        bool execute(JardinRendering* const & garden) override;
};