#pragma once
#include <string>
#include "../../Tokens/Token.h"
#include "../../Tokens/VLToken/VLToken.h"
#include <vector>
#include "../../Error/Errors.h"
#include <functional>
#include <tuple>

class Scanner
{
public:
	Scanner(const std::string& code) : m_code(code) {}

	std::vector<Tokens::Token> ScanTokens();
private:
	inline bool IsAtEnd() const { return m_current >= m_code.size(); }
	inline char Advance() { 
		if (m_code[m_current] == '\n') {
			IncrementLine();
		}
		m_column++;
		return m_code[m_current++];
	}
	inline char Peek() const { return m_code[m_current]; }
	inline char PeekN(int i) const { 
		if (m_current + i >= m_code.size()) return '\0';
		return m_code[m_current + i]; 
	}
	inline bool Match(char expected)  {
		if (IsAtEnd()) return false;
		if (m_code[m_current] != expected) return false;
		m_current++;
		return true;
	}
	inline bool BulkMatch(const std::string& expected) {
		if (IsAtEnd()) return false;
		uint64_t cloneIndex = m_current;
		for (char c : expected) {
			if (c != m_code[cloneIndex++]) return false;
		}
		m_current = cloneIndex;
		return true;
	}
	inline void AddToken(Tokens::TokenType::Type type, uint64_t consumeLength, Tokens::TokenType::masterType masterType = Tokens::TokenType::masterType::NONE) {
		m_tokens.push_back(Tokens::Token(type, consumeLength, m_code.substr(m_current - consumeLength, consumeLength), this->m_line, masterType)); 
	}
	void ScanTillDelim(const std::string& delim, bool throwIfFailed = true);
	inline void Skip() { m_current++; }
	inline bool IsDigit(char c) const { return c >= '0' && c <= '9'; }
	inline bool IsAlpha(char c) const { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
	inline bool IsAlphaNumeric(char c) const { return IsAlpha(c) || IsDigit(c); }
	inline void IncrementLine() { m_line++; m_column = 0; }
	inline void PushToken(Tokens::Token& token) { m_tokens.push_back(token); }
	std::tuple<Tokens::TokenType::Type, uint64_t, Tokens::TokenType::masterType> VerifyTokenType(Tokens::VLTokens::VLToken& matchToken);
	void ScanToken();
	void ScanNumber();
	void ScanIdentifier();
private:
	const std::unordered_map<Tokens::TokenType::Type, std::function<void(Scanner*)>> m_specialCases = {
		{Tokens::TokenType::Type::SingleQuote, [](Scanner* scanner) {
			std::vector<char> returnString;
			returnString.emplace_back(scanner->PeekN(-1)); // Peak 1 back to get the single quote

			char escapeChar = 0x00;
			while (scanner->Peek() != '\'' && !scanner->IsAtEnd() || escapeChar == '\\') {
				if (escapeChar == '\\') {
					escapeChar = 0x00;
					returnString.emplace_back(scanner->Peek());
					scanner->Skip();
					continue;
				}
				if (scanner->Peek() == '\n') {
					scanner->IncrementLine();
				}
				if (scanner->Peek() == '\\') {
					escapeChar = '\\';
					scanner->Skip();
				}
				else {
					returnString.emplace_back(scanner->Peek());
					scanner->Skip();
				}
			}
			if (scanner->IsAtEnd()) {
				Errors::Error("Unterminated String! Line %d", scanner->m_line);
			}
			returnString.emplace_back(scanner->Peek());
			scanner->Skip();
			std::string returnData(returnString.begin(), returnString.end());
			// Make our own token
			Tokens::Token token(Tokens::TokenType::Type::String, returnData.size(), returnData);
			scanner->PushToken(token);
		}},
		{Tokens::TokenType::Type::MultiLineComment, 
		[](Scanner* scanner) {
			scanner->ScanTillDelim("*/");}},
		{Tokens::TokenType::Type::Comment,
		[](Scanner* scanner) {
			scanner->ScanTillDelim("\n", false);}},
	};
	std::vector<Tokens::Token> m_tokens;
	const std::string m_code;
	uint64_t m_current = 0;
	uint64_t m_line = 0;
	uint64_t m_column = 0;
};

