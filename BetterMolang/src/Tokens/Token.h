#pragma once
#include <string>
#include "TokenType/TokenType.h"

namespace Tokens
{
	class Token
	{
	public:
		TokenType::Type type = TokenType::Type::NONE;
		uint64_t ConsumeLength = 1;
		std::string value = "";
		int line = 0;
		TokenType::masterType masterType = TokenType::masterType::NONE;
		Token(TokenType::Type type = TokenType::Type::NONE, uint64_t consumeLength = 1, std::string value = "", int line = 0, Tokens::TokenType::masterType mt = TokenType::masterType::NONE) : type(type), ConsumeLength(consumeLength), value(value), line(line), masterType(mt) {}
	};
}	