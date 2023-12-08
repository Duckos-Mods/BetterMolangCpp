#include "Application.h"
#include "Error/Errors.h"
#include "Lexer/Lexer.h"
#include "RegisterBuilder/RegisterBuilder.h"

Application::Application()
{
	Errors::Info("Starting BetterMolang Compiler!...");
	std::string testString = R"(
var a = ((2 + 1000) * (900 + 419803721983));
)";
	Errors::Info("Parsing Test String Of Value `%s`", testString.c_str());
	auto* lexer = new Lexer();

	auto Tokens = lexer->Tokenize(testString);

	auto* builder = new Transpiler::Transpiler(std::move(Tokens));
	builder->BuildRegisters();
	// Free the scanners memory
	delete lexer;
}