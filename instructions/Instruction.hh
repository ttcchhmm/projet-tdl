#pragma once

#include "../Utils.hh"

/**
 * @brief Represent an atomic instruction modifing the state of the garden or one of its turtles.
 */
class Instruction {
    private:
        /**
         * @brief The targeted turtle.
         */
        std::size_t _turtle;

    public:
        /**
         * @brief Construct a new Instruction. 
         * 
         * @param turtle The targeted turtle.
         */
        explicit Instruction(std::size_t turtle);
        Instruction(Instruction const &) = default;
        virtual ~Instruction() = default;

        /**
         * @brief Execute the instruction.
         *
         * @param garden The JardinRendering instance to work with.
         * @param target The targeted turtle.
         * @return If the instruction is executed as a conditional, the value of the test will be returned.
         *         Otherwise, true will be returned if the execution succeeded and will return false in case of failure.
         */
        virtual bool execute(Field garden);

    protected:
        [[nodiscard]] std::size_t getTarget() const { return _turtle; }
};