#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <vector>
#include <memory>

namespace lsystem
{
    class Production;
    class VertexGenerator;
    class Simulator;

    struct Parameter
    {
        std::string name = "";
        GLfloat value = 0;

        Parameter(std::string const &name, GLfloat value)
            : name(name)
            , value(value)
        {}
    };

    class Symbol
    {
        public: 
            Symbol(std::string const &name)
                : name(name)
            {
                checkName();
            }

            Symbol(Symbol const &s)
                : Symbol(s.name)
            {
                parameters = s.parameters;
                checkName();
            }

            GLfloat operator[](std::string const &parameter_name) const
            {
                auto it = parameters.find(parameter_name);
                if (it == parameters.end())
                {
                    throw std::runtime_error(
                        "Access to non-existent parameter '"
                        + parameter_name + "'");
                }
                return it->second;
            }

            GLfloat &operator[](std::string const &parameter_name)
            {
                auto it = parameters.find(parameter_name);
                if (it == parameters.end())
                {
                    throw std::runtime_error(
                        "Access to non-existent parameter '"
                        + parameter_name + "'");
                }
                return it->second;
            }

            void addParameter(std::string const &name, GLfloat value)
            {
                parameters.insert(std::make_pair(name, value));
            }

            bool operator<(Symbol const &s) const
            {
                return name < s.name;
            }

            std::string const &getName() const
            {
                return name;
            }

        private: 
            void checkName() const
            {
                if (name == "")
                {
                    throw std::runtime_error("Invalid symbol name");
                }
            }

        private:
            std::string name;
            std::map< std::string, GLfloat > parameters; 

            friend class SymbolBuilder;
    };

    typedef std::vector< Symbol > Symbols; 
    typedef std::shared_ptr< Symbols > SymbolsPtr;

} // lsystem

#endif
