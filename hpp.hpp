#ifndef _H_HPP
#define _H_HPP

#include <iostream>				// required includes
#include <cstdlib>
#include <map>
using namespace std;

extern map<string,string*> dat;

extern int yylex();				// lexer interface
extern int yylineno;
extern char* yytext;
#define TOC(X) { yylval.s = new string(yytext); return X; }
extern int yyparse();			// syntax parser interface
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
