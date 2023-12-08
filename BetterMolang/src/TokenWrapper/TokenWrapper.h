#pragma once
#include <vector>
#include "../Tokens/Token.h"
#include "../Tokens/TokenType/TokenType.h"

class TokenWrapper
{
private:
	std::vector<Tokens::Token> m_tokens;
	int m_index = 0;

public:
	TokenWrapper(std::vector<Tokens::Token> tokensConsumption) : m_tokens(tokensConsumption) {}

	inline bool isAtEnd() { return m_index >= m_tokens.size(); }
	inline Tokens::Token& peek() { return m_tokens[m_index]; }
	inline Tokens::Token& peekN(int dist) { 
		if (m_index + dist >= m_tokens.size()) {
			return m_tokens[m_tokens.size() - 1];
		}
		return m_tokens[m_index + dist]; 
	}
	inline bool match(Tokens::TokenType::Type type) { return peek().type == type; }
	inline bool bulkMatch(const std::vector<Tokens::TokenType::Type>& types) {
		if (isAtEnd()) return false;
		int indexClone = m_index;
		for (Tokens::TokenType::Type type : types) {
			if (type != m_tokens[indexClone].type) return false;
		}
		m_index = indexClone;
		return true;
	}
	inline Tokens::Token& advance() { m_index += 1; return m_tokens[m_index-1]; }

	// Returns the current token
	// To allow for multi pass parsing
	void reset() { m_index = 0; }
	// Slow do not use
	std::vector<Tokens::Token> GetTokens() { return m_tokens; }
};

