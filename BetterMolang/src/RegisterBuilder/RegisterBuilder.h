#pragma once
#include "../AST/ASTType.h"
#include "../AST/Statement.h"
#include "../Tokens/Token.h"
#include "../Error/Errors.h"
#include "../TokenWrapper/TokenWrapper.h"
#include "../AST/ObjectRegistery.h"
#include <array>
#include <map>

namespace Transpiler {
    class Transpiler
    {
       
    private:
        void ParseVariableDeclaration();
        AST::BinaryExpression* ParseOutBinaryExpression();
    private:
        ObjectRegistery<AST::VariableDeclaration> m_variable_registery;
        ObjectRegistery<AST::FunctionDeclaration> m_function_registery;
        TokenWrapper m_token_wrapper; // Stores the tokens we are seaching over
    public:

        void BuildRegisters();
        Transpiler(TokenWrapper tokenWrapper) : m_token_wrapper(tokenWrapper) {}
    };
}

