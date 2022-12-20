#ifndef DRIVER_H
#define DRIVER_H

#include <map>
#include <string>
#include <QPoint>
#include <QColor>
#include <QSize>
#include "contexte.hh"
#include "jardinRendering.hh"
#include "Function.hh"

class JardinHandler;

class Driver {
private:      
    JardinHandler * monJardin;
    Contexte variables;

    /**
     * @brief Contains the functions. The key is the function's name and the value is a Function instance.
     */
    std::map<std::string, std::shared_ptr<Function>> functions;

public:
    Driver(JardinHandler * J);
    ~Driver();
    const   Contexte& getContexte() const;
    double  getVariable(const std::string& name) const;
    void    setVariable(const std::string& name, double value);
    JardinRendering* getJardin();

    /**
     * @brief Add the enqueued instructions to a function.
     * 
     * @return True if the function was added, false if it's a redefinition or if the name is empty.
     */
    bool addFunction(std::string const & name, std::list<std::shared_ptr<Instruction>> const & instructions);

    /**
     * @brief Run the main function.
     * 
     * @return True if a main function was found and executed, false otherwise.
     */
    bool runMain();

    /**
     * @brief Get a function by its name.
     * 
     * @param name The function's name.
     * @return A pointer to the function.
     * @throw std::out_of_range if the function is undefined.
     */
    std::shared_ptr<Function>& getFunction(std::string const & name);
};

#endif