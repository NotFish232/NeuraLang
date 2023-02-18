#include <string>

#include <iostream>

#include <vector>

#include <memory>

using namespace std;

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//
namespace AST {

    //base class for all
    class ExprAST {
    public: virtual~ExprAST() {} //virtual meaning a subclass can override this implentation
    };

    //abstract syntax tree for numeric values
    class NumberExprAST: public ExprAST {
        double Val;

    public:
        //initializer list, assigns variable to class.  think getters & setters
        NumberExprAST(double Val): Val(Val) {}
    };

    //syntax tree for variables
    class VariableExprAST: public ExprAST {
        std::string Name;

    public:
        VariableExprAST(const std::string & Name): Name(Name) {}
    };

    //syntax tree for binary
    class BinaryExprAST: public ExprAST {
        char Op;
        std::unique_ptr < ExprAST > LHS, RHS;

    public:
        BinaryExprAST(char op, std::unique_ptr < ExprAST > LHS, std::unique_ptr < ExprAST > RHS): Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

    //function calls syntax tree
    class CallExprAST: public ExprAST {
        std::string Callee;
        std::vector < std::unique_ptr < ExprAST >> Args;

    public:
        CallExprAST(const std::string & Callee, std::vector < std::unique_ptr < ExprAST >> Args): Callee(Callee), Args(std::move(Args)) {}
    };

    //prototype function syntax tree, captures the name and the arguments
    //basically represents the function, as a prototype.
    class PrototypeAST {
        std::string Name;
        std::vector < std::string > Args;

    public:
        PrototypeAST(const std::string & Name, std::vector < std::string > Args): Name(Name), Args(std::move(Args)) {}

        const std::string & getName() const {
            return Name;
        }
    };

    //function syntax tree
    //this represents the function itself.
    class FunctionAST {
        std::unique_ptr < PrototypeAST > Proto;
        std::unique_ptr < ExprAST > Body;

    public:
        FunctionAST(std::unique_ptr < PrototypeAST > Proto, std::unique_ptr < ExprAST > Body): Proto(std::move(Proto)), Body(std::move(Body)) {}
    };
}