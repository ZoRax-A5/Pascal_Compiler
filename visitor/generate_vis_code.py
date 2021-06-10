"""
auto generate visitor header code
virtual void visitASTNode(ASTNode* node) = 0;
"""

s = ''
with open('../parser/data/class_name') as f:
    s += f.read()
lst = s.split()
for l in lst:
    # abstract class
    print('virtual void visit{}(const {}* node) = 0;'.format(l, l))
    # concrete class
    # print('void CLIVisual::visit{}({}* node);'.format(l, l))
    # concrete class method
    # print('void '+l+'::accept(Visitor* visitor) const { visitor->visit'+l+'(this); }')
