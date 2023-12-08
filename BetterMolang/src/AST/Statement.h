#pragma once
#include "ASTType.h"
#include "../Tokens/Token.h"
#include "../Error/Errors.h"
#include "../TokenWrapper/TokenWrapper.h"
#include "ObjectRegistery.h"
#include <stdexcept>
#include <array>
#include <map>

namespace AST
{
    class Statement
    {
    private:
        ASTType m_type;
    public:
        inline ASTType GetType() {
            return ASTType::None; 
        }
        Statement(ASTType type) : m_type(type) {}
	};

    class Expression : public Statement
    {
    public:
        Expression(ASTType type) : Statement(type) {}
        virtual std::string ToString() { return ""; }
	};

    class BinaryExpression : public Expression
    {
    public:
		int line;
        Tokens::Token op;
        Expression* left;
        Expression* right;

        BinaryExpression(int line, Tokens::Token op, Expression* left, Expression* right) : line(line), op(op), left(left), right(right), Expression(ASTType::BinaryExpression) {}
        ~BinaryExpression() { delete left; delete right; }

        std::string ToString() override
        {
            //i should be using a format string here but i dont want to
			return "(" + left->ToString() + " " + op.value + " " + right->ToString() + ")";
		}
	};

    class VariableExpression : public Expression
    {
    public:
        int line;
		std::string name;

		VariableExpression(int line, std::string name) : line(line), name(name), Expression(ASTType::VariableExpression) {}
        std::string ToString() override
        {
            return name;
        }
    };

    class VaiableStatic : public Expression
    {
    public:
        int line;
        std::string value;

        VaiableStatic(int line, std::string value) : line(line), value(value), Expression(ASTType::VariableStatic) {}
        std::string ToString() override
        {
			return value;
		}
    };

    class VariableDeclaration : public Statement
    {
    public:
        int line;
        std::string name; // We dont handle types we just hope that the DSL knows what it is doing
        Expression* value;

        VariableDeclaration(int line, std::string name, Expression* value) : line(line), name(name), value(value), Statement(ASTType::VariableDecel) {}
        VariableDeclaration(int line) : line(line), Statement(ASTType::VariableDecel) {}
        VariableDeclaration() : Statement(ASTType::VariableDecel) {} // Only exists so C++ doesnt have a fit
        ~VariableDeclaration() { delete value; }

        std::string ToString()
        {
            if (value == nullptr) return name + ";";
            return name + " = " + value->ToString();
        }
    };

    class FunctionDeclaration
    {
    public:
        int line;
		std::string name;
		std::vector<std::string> args;
		std::vector<AST::Statement*> body;

		FunctionDeclaration(int line, std::string name, std::vector<std::string> args, std::vector<AST::Statement*> body) : line(line), name(name), args(args), body(body) {}
        ~FunctionDeclaration() { for (auto& statement : body) delete statement; }
	};
}

