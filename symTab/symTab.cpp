#include "symTab.h"

static int current_depth = -1;
static int memloc[1024];
static vector<Scope> scopeStack;//scope in the stack
static vector<Scope> scopes;//All scope

static int hashfunction(string str) {
	int value = 0;
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
	ScopeNode* temp = new ScopeNode(Name, pScope);
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
	SYMTABListNode* temp_node = new SYMTABListNode(name, lineNum, memloc[current_depth], recType, dataType);
	int hashvalue = hashfunction(name);
	SYMTABList insert_list = nscope->hashTab[hashvalue];
	for (auto traver_node : insert_list) {
		if (traver_node.Name == name) {
			traver_node.lines.push_back(lineNum);
			cout << "Error! In line [" << lineNum << "]: '" << name << "' is already defined." << endl;
			delete temp_node;
			exit(-1);
		}
	}
	insert_list.push_back(temp_node);
	memloc[current_depth] += loc_shift;
}
//For the examination of datatype
string STfind(string name) {
	int hashvalue = hashfunction(name);
	
	Scope nscope = Stop();
	SYMTABList insert_list = nscope->hashTab[hashvalue];
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
		cout << "Scope Name: " << nscope->Name << " <depth: " << nscope->depth << ">" << endl;
		for (int i = 0; i < TABLE_SIZE;i++) {
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
	int hashValue = hashfunction(name);
	Scope nscope = Sfind(scope);
	while (nscope) {
		for (auto nsym : nscope->hashTab[hashValue]) {
			if (nsym.Name == name) {
				return nsym.recType == "Const";
			}
		}
		nscope = nscope->pScopeNode;
	}
	return false;
}
string sym::getIDType(string name, string scope) {
	int hashValue = hashfunction(name);
	Scope nscope = Sfind(scope);
	while (nscope) {
		for (auto nsym : nscope->hashTab[hashValue]) {
			if (nsym.name == name) {
				return nsym.dataType;
			}
		}
		nscope = nscope->pScopeNode;
	}
	return "";
}
string sym::getArrayType(string name, string scope) {
	Scope nscope = Sfind(scope);
	while (nscope) {
		for (auto item : nscope->ArrList) {
			if (item.Name == name) {
				return item.Type;
			}
		}
		nscope = nscope->pScopeNode;
	}
	return "";
}

string sym::getRecordElementType(string name, string MEMname, string scope) {
	for (auto scope : scopes) {
		if (scope->Name == name) {
			int hashValue = hashfunction(MEMname);
			for (auto nsym : scope->hashTab[hashValue]) {
				if (nsym.Name == MEMname) {
					return nsym.dataType;
				}
			}
		}
	}

	return "";
}

int sym::getArrayBegin(string name, string scope) {
	Scope nscope = Sfind(scope);
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

int sym::getNodeNum(string name, string MEMname, string scope) {


	for (auto nscope : scopes) {
		if (nscope->Name == name) {
			int hashValue = hashfunction(MEMname);
			for (auto nsym : nscope->hashTab[hashValue]) {
				if (nsym.Name == MEMname) {
					return nsym.order;
				}
			}
		}
	}
	return -1;

}