#pragma once
#include "../TokenType/TokenType.h"
#include "../Token.h"

namespace Tokens
{
    namespace VLTokens
    {
        class VLTokenNode
        {
        public:
            Tokens::TokenType::Type TokenT;
            Tokens::TokenType::masterType masterType = Tokens::TokenType::masterType::NONE;
            char SelfValue;
            std::vector<VLTokenNode> Children;

            VLTokenNode(Tokens::TokenType::Type tokenT, char selfValue, std::vector<VLTokenNode> children, Tokens::TokenType::masterType mt = Tokens::TokenType::masterType::NONE) : TokenT(tokenT), SelfValue(selfValue), Children(children), masterType(mt) {}
        };

        class VLToken
        {
        public:
            Tokens::TokenType::Type TokenT;
            Tokens::TokenType::masterType masterType = Tokens::TokenType::masterType::NONE;
            uint64_t ConsumeLength;
            std::vector<VLTokenNode> Children;

            VLToken(Tokens::TokenType::Type tokenT, uint64_t consumeLength, std::vector<VLTokenNode> children, Tokens::TokenType::masterType mt = Tokens::TokenType::masterType::NONE) : TokenT(tokenT), ConsumeLength(consumeLength), Children(children), masterType(mt) {}
        };
    }
}
