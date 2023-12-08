#pragma once
#include <vector>
#include "Scanner/Scanner.h"
#include "../TokenWrapper/TokenWrapper.h"
class Lexer
{
public:
	Lexer() {};

	inline TokenWrapper Tokenize(const std::string& source)
	{
		Scanner scanner(source);
		std::vector<Tokens::Token> tokens = scanner.ScanTokens();
		return std::move(TokenWrapper(std::move(tokens)));// To avoid copy
	}
};

