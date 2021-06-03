#include "ast.hpp"

/* AST node base class */
ASTNode::ASTNode() {}
std::pair <int, int> ASTNode::getLocation(void) {
    return std::make_pair(this->line_num, this->col_num);
}
void ASTNode::setLocation(int line, int col) {
    this->line_num = line;
    this->col_num = col;
}