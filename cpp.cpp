#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() {
	// .neutral parse
	yyparse();
	// .dat
	cout << "\n\n=================\n\n";
	for (auto it=pcb.begin(),e=pcb.end();it!=e;it++)
		cout << "\n"<<it->first << it->second->dump(1) << endl;
	// .dsn
	ofstream dsn("dsn.dsn");
	dsn << "(pcb "<<pcb["BOARD"]->val << "\n";					// BOARD
	dsn << "\t(resolution " << pcb["B_UNITS"]->val << " 100)\n";// B_UNITS
															// pcb structure
	dsn << "\t(structure\n";								
	dsn << "\t\t(boundary (path pcb 0.5 ";					// outline polygon
	Sym* BE = pcb["BOARD_EDGE_OUTLINE"];
	for (int i=0;i<BE->size();i++)
		dsn << BE->nest[i]->nest[0]->val<<" "<<BE->nest[i]->nest[1]->val<<" ";
	dsn << "))\n";
	dsn << "\t\t(layer bot (type signal))\n";
	dsn << "\t)\n";
	dsn << ")\n";
}

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return val; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

int Sym::size() { return nest.size(); }

map<string,Sym*> pcb;

Str::Str(string V):Sym(V){}
string Str::head() { return "'"+val+"'"; }

List::List():Sym("[]"){}

