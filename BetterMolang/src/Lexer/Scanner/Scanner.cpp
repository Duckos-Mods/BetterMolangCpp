#include "Scanner.h"
#include "../../Tokens/TokenType/TokenRelated.h"
#include <algorithm>

void Scanner::ScanTillDelim(const std::string& delim, bool throwIfFailed) {
	std::vector<char> buffer;
	// Set the buffer to the size of the delimiter
	buffer.resize(delim.size());
	std::for_each(buffer.begin(), buffer.end(), [&](char& c) { c = Advance(); });
	// We dont to test against the first buffer
	while (!IsAtEnd()) {
		// If the buffer matches the delimiter, we can return
		if (std::equal(buffer.begin(), buffer.end(), delim.begin())) return;
		// Shift the buffer
		for (int i = 0; i < buffer.size() - 1; i++) {
			buffer[i] = buffer[i + 1];
		}
		// Add the next character to the buffer
		buffer[buffer.size() - 1] = Advance();
	}
	if (throwIfFailed) {
		Errors::Error("Unexpected end of file, %d, %d", m_line, m_column);
	}
	else {
		Errors::Warning("Unexpected end of file, %d, %d", m_line, m_column);
	}
}

std::tuple<Tokens::TokenType::Type, uint64_t, Tokens::TokenType::masterType> Scanner::VerifyTokenType(Tokens::VLTokens::VLToken& matchToken) {
	if (this->IsAtEnd()) {
		return std::make_tuple(matchToken.TokenT, matchToken.ConsumeLength, matchToken.masterType);
	}
	// If the token has no children, we can just return the token
	if (matchToken.Children.size() == 0) {
		return std::make_tuple(matchToken.TokenT, matchToken.ConsumeLength, matchToken.masterType);
	}

	// If the token has children, we need to check what token type it is by seaerching forward more 
	for (auto& child : matchToken.Children) {
		uint64_t consumeLength = matchToken.ConsumeLength; // The consume length of the token
		std::vector<char> bulkMatchBuffer; // The buffer to bulk match against
		Tokens::VLTokens::VLTokenNode *tempNode = &child; // The current node we are on
		while (true) {
			bulkMatchBuffer.emplace_back(tempNode->SelfValue); // Add the next character to the buffer
			consumeLength++; // Increment the consume length
			if (tempNode->Children.size() == 0) { // If the current node has no children, we can break the tree walk
				break;
			}
			// If the  current node has children, We need to add them to the buffer
			child = tempNode->Children[0]; // Set the current node to the first child, We dont support multiple children yet!
		}
		// If the buffer matches the token, we can return the token type
		const std::string bulkMatchBufferStr(bulkMatchBuffer.begin(), bulkMatchBuffer.end());
		if (BulkMatch(bulkMatchBufferStr)) {
			return std::make_tuple(tempNode->TokenT, consumeLength, tempNode->masterType);
		}
	}
	return std::make_tuple(matchToken.TokenT, matchToken.ConsumeLength, matchToken.masterType);
}

std::vector<Tokens::Token> Scanner::ScanTokens() {
	while (!IsAtEnd()) {
		ScanToken();
	}
	return std::move(m_tokens);
}

void Scanner::ScanToken() {
	char c = Advance();
	switch (c) {
	case '\n': {
		IncrementLine();
		break;
	}
		case ' ':
		case '\r':
		case '\t':
		return;
	}

	auto it = Tokens::TokenRelated::VlTokenMap.find(c);
	if (it != Tokens::TokenRelated::VlTokenMap.end()) {
		auto token = VerifyTokenType(it->second);
		auto tokenType = std::get<0>(token);
		auto consumeLength = std::get<1>(token);

		auto SpecialMatch = m_specialCases.find(tokenType);
		if (SpecialMatch != m_specialCases.end()) {
			SpecialMatch->second(this);
			return;
		}
		else {
			if (Tokens::TokenType::Type::Null == tokenType) {
				Errors::Error("Unknown Token at %d, %d", m_line, m_column);
			}
			AddToken(tokenType, consumeLength, std::get<2>(token));
			return;
		}
	}
	else if (IsDigit(c)) {
		ScanNumber();
		return;
	}
	else if (IsAlpha(c)) {
		ScanIdentifier();
		return;
	} 
}

void Scanner::ScanNumber() {
	int consumeLength = 1;
	while (IsDigit(Peek())) {
		consumeLength++;
		this->Advance();
	}
	if (Peek() == '.' && IsDigit(this->PeekN(1))) {
		consumeLength++;
		this->Advance();
		while (IsDigit(Peek())) {
			consumeLength++;
			this->Advance();
		}
	}
	AddToken(Tokens::TokenType::Type::Number, consumeLength);
}

void Scanner::ScanIdentifier() {
	int consumeLength = 1;
	while (IsAlphaNumeric(Peek())) {
		consumeLength++;
		this->Advance();
	}

	// Check if the identifier is a keyword
	std::string identifier = m_code.substr(m_current - consumeLength, consumeLength);
	auto it = Tokens::TokenRelated::keywords.find(identifier);
	if (it != Tokens::TokenRelated::keywords.end()) {
		AddToken(it->second, consumeLength);
		return;
	}
	else {
		AddToken(Tokens::TokenType::Type::Identifier, consumeLength);
	}
}