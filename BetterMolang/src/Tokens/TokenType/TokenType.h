#pragma once
#include <unordered_map>
#include <string>

namespace Tokens {

    namespace TokenType
    {
        // To stop C++ from complaining about the enum class
        enum class masterType {
            NONE,
            Operator
        };

        enum Type
        {
            NONE,
            // Single - character tokens.
            LeftParen,
            RightParen,
            LeftBrace,
            RightBrace,
            LeftBracket,
            RightBracket,
            //LeftArrow,
            //RightArrow,
            Comma,
            Dot,
            Semicolon,
            SingleQuote,

            // One or two character tokens.
            Bang,
            BangEqual,
            Equal,
            EqualEqual,
            Greater,
            GreaterEqual,
            Less,
            LessEqual,
            PlusEqual,
            Plus,
            MinusEqual,
            EntitySelector,
            Minus,
            StarEqual,
            Star,
            SlashEqual,
            Slash,
            PlusPlus,
            MinusMinus,
            AndAnd,
            OrOr,
            Question,
            NullCoalesce,
            // Special tokens
            Comment,
            MultiLineComment,
            Macro, // Will handle this later

            // Literals.
            Identifier,
            String,
            Number,

            // Keywords.
            And_,
            Break,
            Array,
            Else,
            If,
            False,
            For,
            Function,
            Null,
            Or_,
            Return,
            True,
            Var,
            Struct,
            This,
            Foreach,
            Continue,
            Query,
            Math,
            Geometry,
            Texture,
            Material,

            EOF_
        };
    }
}