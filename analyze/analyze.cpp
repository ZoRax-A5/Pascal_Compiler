#include "analyze.h"

void SYMTABbuild(ASTProgram* Tree) {
	Scope global = Screate("global");
	//Tree->scope = global;
	traverse_Build(Tree);
	Spop();
	STprint();
}

void typeCheck(ASTProgram* Tree) {
	traverse_back(Tree);
}

static void traverse_Build(ASTProgram* node) {
	node->accept(this);
}

static void traverse_back(ASTProgram* node) {

}

static bool canChange(string type1, string type2) {

}