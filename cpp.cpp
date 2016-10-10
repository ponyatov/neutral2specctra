#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { yyparse();
	cout << "\n\n=================\n\n";
	for (auto it=dat.begin(),e=dat.end();it!=e;it++)
		cout << it->first << "\n\t" << *(it->second) << endl;
}

map<string,string*> dat;

