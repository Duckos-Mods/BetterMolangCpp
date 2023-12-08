#include "RegisterBuilder.h"

namespace Transpiler
{
	void Transpiler::BuildRegisters()
	{
		ParseVariableDeclaration();
	}

	void Transpiler::ParseVariableDeclaration()
	{
		while (!this->m_token_wrapper.isAtEnd())
		{
			// Pull the next token and see if it is a variable declaration if not continue
			auto token = m_token_wrapper.advance();
			if (token.type != Tokens::TokenType::Var) continue;
			if (token.type == Tokens::TokenType::Semicolon) continue;
			AST::VariableDeclaration varDec(token.line);

			// Parse out the variable name
			token = m_token_wrapper.advance();
			if (token.type != Tokens::TokenType::Identifier) Errors::Error("Expected Identifier at %d instead got %s", token.line, token.value);
			varDec.name = token.value;
			
			// Parse out the variable assignment and if there isnt one then register the variable as uninitialized
			token = m_token_wrapper.advance();
			if (token.type != Tokens::TokenType::Equal)
			{
				Errors::Warning("Unintaialized variable at %d", token.line);
				m_variable_registery.RegisterObject(varDec.name, varDec);
				continue;
			}
			// Parse out the variable value we should be using a better way of handling the types than oror spam lol
			token = m_token_wrapper.advance();
			if (token.type == Tokens::TokenType::Number || token.type == Tokens::TokenType::String || token.type == Tokens::TokenType::Identifier)
			{
				varDec.value = new AST::VaiableStatic(token.line, token.value);
			}
			else
			{
				varDec.value = ParseOutBinaryExpression();
			}
			// 
			m_variable_registery.RegisterObject(varDec.name, varDec);
			std::string wholeVar = varDec.ToString();
			Errors::Info("Registered Variable %s", wholeVar.c_str());
		}
	}

	AST::BinaryExpression* Transpiler::ParseOutBinaryExpression()
	{
		auto token = m_token_wrapper.advance();
		if (token.type == Tokens::TokenType::Semicolon) Errors::Error("Unexpected Semicolon at %d", token.line);

		AST::Expression* left = nullptr;
		AST::Expression* right = nullptr;
		Tokens::Token op;
		// Parse out the left side of the expression
		while (token.type != Tokens::TokenType::Semicolon && token.type != Tokens::TokenType::RightParen)
		{
			if (token.type == Tokens::TokenType::Identifier)
			{

				left = new AST::VariableExpression(token.line, token.value);
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else if (token.type == Tokens::TokenType::Number || token.type == Tokens::TokenType::String)
			{
				left = new AST::VaiableStatic(token.line, token.value);
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else if (token.type == Tokens::TokenType::LeftParen)
			{
				// Parse out the expression
				left = ParseOutBinaryExpression();
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else
			{
				Errors::Error("Unexpected Token at %d", token.line);
			}

		}
		
		// Parse out the operator
		if (token.masterType != Tokens::TokenType::masterType::Operator) 
			Errors::Error("Expected Operator at %d", token.line);
		op = token;

		token = m_token_wrapper.advance();
		// Parse out the right side of the expression
		while (token.type != Tokens::TokenType::Semicolon && token.type != Tokens::TokenType::RightParen)
		{
			if (token.type == Tokens::TokenType::Identifier)
			{

				right = new AST::VariableExpression(token.line, token.value);
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else if (token.type == Tokens::TokenType::Number || token.type == Tokens::TokenType::String)
			{
				right = new AST::VaiableStatic(token.line, token.value);
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else if (token.type == Tokens::TokenType::LeftParen)
			{
				// Parse out the expression
				right = ParseOutBinaryExpression();
				token = m_token_wrapper.advance();
				break; // Break out of the loop
			}
			else
			{
				Errors::Error("Unexpected Token at %d", token.line);
			}

		}
		if (token.type != Tokens::TokenType::RightParen) 
			Errors::Error("Expected Right Paren at %d", token.line);

		return new AST::BinaryExpression(token.line, op, left, right);
	}
}