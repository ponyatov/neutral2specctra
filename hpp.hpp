#ifndef _H_HPP
#define _H_HPP

#include <iostream>				// required includes
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string val;
	Sym(string);
	vector<Sym*> nest; void push(Sym*);
	map<string,Sym*> lookup;
	virtual string head(); string pad(int);
	virtual string dump(int=0);
	virtual int size();
};

extern map<string,Sym*> pcb;
extern void pcb_init();

struct Str:Sym { Str(string); string head(); };

struct List:Sym { List(); };

extern int yylex();				// lexer interface
extern int yylineno;
extern char* yytext;
#define TOC(X) { yylval.o = new Sym(yytext); return X; }
extern int yyparse();			// syntax parser interface
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
