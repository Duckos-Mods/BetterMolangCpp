#pragma once
#include <unordered_map>
#include <string>
#include "TokenType.h"
#include "../VLToken/VLToken.h"

namespace Tokens
{

    namespace TokenRelated {
        static std::unordered_map<std::string, TokenType::Type> keywords = {
            {"and", TokenType::And_},
            {"break", TokenType::Break},
            {"else", TokenType::Else},
            {"false", TokenType::False},
            {"for", TokenType::For},
            {"function", TokenType::Function},
            {"if", TokenType::If},
            {"null", TokenType::Null},
            {"or", TokenType::Or_},
            {"return", TokenType::Return},
            {"true", TokenType::True},
            {"var", TokenType::Var},
            {"struct", TokenType::Struct},
            {"this", TokenType::This},
            {"foreach", TokenType::Foreach},
            {"continue", TokenType::Continue},
            {"query", TokenType::Query},
            {"math", TokenType::Math},
            {"geometry", TokenType::Geometry},
            {"texture", TokenType::Texture},
            {"material", TokenType::Material}
        };

        static std::unordered_map<char, Tokens::VLTokens::VLToken> VlTokenMap = {
            {'!', VLTokens::VLToken(
                TokenType::Bang,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::BangEqual, '=', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'=', VLTokens::VLToken(
                TokenType::Equal,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::EqualEqual, '=', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'>', VLTokens::VLToken(
                TokenType::Greater,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::GreaterEqual, '=', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'<', VLTokens::VLToken(
                TokenType::Less,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::LessEqual, '=', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'+', VLTokens::VLToken(
                TokenType::Plus,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::PlusEqual, '=', {}, TokenType::masterType::Operator),
                    VLTokens::VLTokenNode(TokenType::PlusPlus, '+', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'-', VLTokens::VLToken(
                TokenType::Minus,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::MinusEqual, '=', {}, TokenType::masterType::Operator),
                    VLTokens::VLTokenNode(TokenType::MinusMinus, '-', {}, TokenType::masterType::Operator),
                    VLTokens::VLTokenNode(TokenType::EntitySelector, '>', {}),
                },
                TokenType::masterType::Operator)},

            {'*', VLTokens::VLToken(
                TokenType::Star,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::StarEqual, '=', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'/', VLTokens::VLToken(
                TokenType::Slash,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::SlashEqual, '=', {}, TokenType::masterType::Operator),
                    VLTokens::VLTokenNode(TokenType::Comment, '/', {}),
                    VLTokens::VLTokenNode(TokenType::MultiLineComment, '*', {}),
                },
                TokenType::masterType::Operator)},
            {'&', VLTokens::VLToken(
                TokenType::Null,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::AndAnd, '&', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'|', VLTokens::VLToken(
                TokenType::Null,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::OrOr, '|', {}, TokenType::masterType::Operator),
                },
                TokenType::masterType::Operator)},
            {'?', VLTokens::VLToken(
                TokenType::Question,
                1,
                {
                    VLTokens::VLTokenNode(TokenType::NullCoalesce, '?', {}),
                })},
            {';', VLTokens::VLToken(
                TokenType::Semicolon,
                1,
                {})},
            {',', VLTokens::VLToken(
                TokenType::Comma,
                1,
                {})},
            {'.', VLTokens::VLToken(
                TokenType::Dot,
                1,
                {})},
            {'\'', VLTokens::VLToken(
                TokenType::SingleQuote,
                1,
                {})},
            {'(', VLTokens::VLToken(
                TokenType::LeftParen,
                1,
                {})},
            {')', VLTokens::VLToken(
                TokenType::RightParen,
                1,
                {})},
            {'{', VLTokens::VLToken(
                TokenType::LeftBrace,
                1,
                {})},
            { '}', VLTokens::VLToken(
                TokenType::RightBrace,
                1,
                {})},
            { '[', VLTokens::VLToken(
                TokenType::LeftBracket,
                1,
                {})},
            { ']', VLTokens::VLToken(
                TokenType::RightBracket,
                1,
                {}
            )}
        };
    }
}