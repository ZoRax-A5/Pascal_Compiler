#include "analyze.h"

void SYMTABbuild(ASTProgram* Tree) {
	Scope global = Screate("global");
	Tree->scope = global;
	traverse_Build(Tree);
	sc_pop();
	st_print();
}

void typeCheck(ASTNode* Tree) {
	traverse(Tree, pushScope, checkNode);
}

static void traverse_Build(ASTProgram* node) {
	node->accept();

}

static void insertNode(ASTNode node) {

}

static void checkNode(ASTNode node) {

}

static void popScope(ASTNode node) {

}

static void pushScope(ASTNode node) {

}

static bool canChange(string type1, string type2) {

}