#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { 
	// .neutral parse
	pcb_init(); yyparse();
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
	// \ outline polygon
	dsn << "\t\t(boundary (path pcb 0.5 ";					
	Sym* BE = pcb["BOARD_EDGE_OUTLINE"];
	for (int i=0;i<BE->size();i++)
		dsn << BE->nest[i]->nest[0]->val<<" "<<BE->nest[i]->nest[1]->val<<" ";
	dsn << "))\n";
	// /
	// \ layers
	Sym* LE = pcb["layer"];
	for (auto it=LE->lookup.begin(),e=LE->lookup.end();it!=e;it++)
		dsn << "\t\t(layer " << it->first << " (type signal))\n";
	// /
	// \ vias
	dsn << "\t\t(via via)\n";
	// /
	dsn << "\t)\n";
	// \ network
	dsn << "\t(network\n";
	Sym *NW = pcb["net"]; int nets=0;
	for (auto it=NW->lookup.begin(),e=NW->lookup.end();it!=e && nets<125;it++,nets++)
			dsn << "\t\t(net " << it->first << ")\n";
	dsn << "\t)\n";
	// /
	dsn << ")\n";
}

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return val; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=lookup.begin(),e=lookup.end();it!=e;it++)
		S += "\n"+pad(depth+1)+it->first+"="+it->second->dump(depth+2);
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

int Sym::size() { return nest.size(); }

Str::Str(string V):Sym(V){}
string Str::head() { return "'"+val+"'"; }

List::List():Sym("[]"){}

map<string,Sym*> pcb;

void pcb_init() {
	pcb["pad"]=new Sym("pad");
	pcb["layer"]=new Sym("layer");
	pcb["net"]=new Sym("net");
}
