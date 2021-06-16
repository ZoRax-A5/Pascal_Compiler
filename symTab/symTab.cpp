#include "symTab.h"
using namespace std;

static int current_depth = -1;
static int memloc[1024];
static vector<Scope> scopeStack;//scope in the stack
static vector<Scope> scopes;//All scope

static int hash(string str) {
	int v = 0;
	for (int i = 0; i < str.length(); i++) {
		value = value << SHIFT;
		value += str[i];
		value = value % TABLE_SIZE;
	}
	return value;
}

Scope Screate(string name) {//创建一个链表头并且初始化depth
	Scope temp = new ScopeNode(name);
	current_depth++;
	if (current_depth == 0) {
		temp->pScopeNode = nullptr;
	}
	else temp->pScopeNode = scopeStack[current_depth - 1];
	if (current_depth==0||temp->pScopeNode->Name == "global") memloc[current_depth] = 0;
	else memloc[current_depth] = memloc[current_depth - 1];
	scopeStack.push_back(temp);
	scopes.push_back(temp);
	return temp;

}

Scope Screate(string Name, Scope pScope) {
	ScopeNode temp = new ScopeNode(Name, pScope);
	scopes.push_back(temp);
	return temp;
}

void Spop() {
	current_depth--;
	scopeStack.pop_back();
}

Scope Stop() {
	return scopeStack[current_depth - 1];
}

void Spush(string name) {
	Scope temp = new ScopeNode(name);
	scopeStack.push_back(temp);
	current_depth++;
}

Scope Sfind(string name) {
	for (auto scope : scopes) {
		if (scope->Name == name) {
			return scope;
		}
	}
	return Sfind("global");//返回global或者NULL?等待修改
}

void STinsert(string name, int lineNum, int loc_shift, string recType, string dataType) {
	Scope nscope = Stop();
	SYMTABListNode temp_node = new SYMTABListNode(name, lineNum, memloc[current_depth], recType, dataType);
	int hashvalue = hash(name);
	SYMTABList insert_list = nscope->hashTab[hashvalue];
	for (auto traver_node : insert_list) {
		if (traver_node.Name == name) {
			traver_node.lines.push_back(linenum);
			cout << "Error! In line [" << lineNum << "]: '" << name << "' is already defined." << endl;
			delete temp_node;
			exit(-1);
		}
	}
	insert_list.push_back(tempnode);
	memloc[current_depth] += loc_shift;
}
//For the examination of datatype
string STfind(string name) {
	int hashvalue = hash(name);
	SYMTABList insert_list = nscope->hashTab[hashvalue];
	Scope nscope = Stop();
	while (nscope) {
		for (auto traver_node : insert_list) {
			if (traver_node.Name == name) {
				return traver_node.dataType;
			}
		}
		nscope = nscope->pScopeNode;
	}
	return "";
}

void STprint() {
	for (auto nscope : scopes) {
		cout << "-----------------------------------------------" << endl;
		cout << "Scope Name: " << item->scopeName << " <depth: " << item->depth << ">" << endl;
		for (auto i:TABLE_SIZE) {
			SYMTABList symtab = nscope->hashTab[i];
			if (symtab.size() == 0) {
				continue;
			}
			
			for (auto nsym:symtab) {
				cout.setf(ios::left);
				cout.width(12);
				cout << nsym.Name;
				cout.setf(ios::left);
				cout.width(12);
				cout << nsym.recType;
				cout.setf(ios::left);
				cout.width(12);
				cout << nsym.dataType;
				cout.setf(ios::left);
				cout.width(12);
				cout << nsym.memloc;
				cout.setf(ios::left);
				cout.width(12);
				cout << nsym.order;
				for (auto lineNo : nsym.lines) {
					cout << lineNo << " ";
				}
				if (nsym.dataType == "Array") {
					int begin, end;
					string type;
					for (auto arr : nscope->ArrList) {
						if (arr.Name == nsym.Name) {
							begin = arr.arrayBegin;
							end = arr.arrayEnd;
							type = arr.Type;
							break;
						}
					}
					cout << '\t' << "<Array: range [" << begin << ":" << end << "], type " << type << " >";
				}
				cout << endl;

			}
		}
		cout << "-----------------------------------------------" << endl;
	}
}

bool sym::getIDIsConst(string name, string scope) {
	int hashValue = hashFunc(name);
	Scope nscope = Sfind(scope);
	while (nscope) {
		for (auto nsym : nscope->hashTable[hashValue]) {
			if (nsym.name == name) {
				return nsym.recType == "Const";
			}
		}
		nscope = nscope->pScopeNode;
	}
	return false;
}
string sym::getIDType(string name, string scope) {
	int hashValue = hash(name);
	Scope nscope = Sfind(scope);
	while (nscope) {
		for (auto nsym : nscope->hashTable[hashValue]) {
			if (nsym.name == name) {
				return nsym.dataType;
			}
		}
		nscope = nscope->pScopeNode;
	}
	return "";
}
string sym::getArrayType(string name, string scope) {
	Scope nscope = getscope(scope);
	while (nscope) {
		for (auto item : nscope->arrayList) {
			if (item.Name == name) {
				return item.Type;
			}
		}
		nscope = nscope->parentScope;
	}
	return "";
}

string sym::getRecordElementType(string name, string MEMname, string scope) {
	for (auto scope : scopes) {
		if (scope->scopeName == name) {
			int hashValue = hashFunc(MEMname);
			for (auto nsym : scope->hashTable[hashValue]) {
				if (nsym.name == MEMname) {
					return nsym.dataType;
				}
			}
		}
	}

	return "";
}

int sym::getArrayBegin(string name, string scope) {
	Scope nscope = getscope(scope);
	while (nscope) {
		for (auto arr : nscope->ArrList) {
			if (arr.Name == name) {
				return arr.arrayBegin;
			}
		}
		nscope = nscope->parentScope;
	}
	return -1;
}

int sym::getRecordNo(string name, string MEMname, string scope) {


	for (auto nscope : scopes) {
		if (nscope->scopeName == name) {
			int hashValue = hashFunc(MEMname);
			for (auto nsym : scope->hashTable[hashValue]) {
				if (nsym.name == MEMname) {
					return nsym.order;
				}
			}
		}
	}
	return -1;

}