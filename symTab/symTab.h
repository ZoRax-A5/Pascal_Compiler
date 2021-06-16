#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

#define TABLE_SIZE 571
#define SHIFT 4

class SYMTABArray {
public:
	string Name;
	int arrayBegin;
	int arrayEnd;
	string Type;
	SYMTABArray(string _Name,int _arrayBegin,int _arrayEnd,string _Type):
	Name(_Name),arrayBegin(_arrayBegin),arrayEnd(_arrayEnd),Type(_Type){}
	SYMTABArray(string newName, SYMTABArray arr):
	Name(newName),arrayBegin(arr.arrayBegin),arrayEnd(arr.arrayEnd),Type(arr.Type){}
};

class SYMTABListNode {
public:
	string Name;//Table name
	vector<int> lines;//lines' information
	int memloc;//memory location
	string recType;//function,const,variable
	string dataType;
	int order;//the order of the defined variable

	SYMTABListNode(string _Name, int _linenum, int _memloc, string _recType, string _dataType, int order) :id(_id), memloc(_memloc), recType(_recType), dataType(_dataType), order(_order) {
		lines.push_back(_linenum);
	}

};

typedef vector<SYMTABListNode> SYMTABList;

class ScopeNode {
public:
	string Name;
	int depth;
	ScopeNode* pScopeNode;
	SYMTABList hashTab[TABLE_SIZE];
	map<string, string> userDefType;
	vector<SYMTABArray> ArrList;
	int order;

	ScopeNode(string _Name):Name(_Name),order(0){}
	ScopeNode(string _Name, ScopeNode* _pScopeNode) :
		Name(_Name), depth(_pScopeNode->depth), pScopeNode(_pScopeNode->pScopeNode), userDefType(_pScopeNode->userDefType), ArrList(_pScopeNode->ArrList), order(0) {
		for (int i = 0; i < TABLE_SIZE; i++) {
			hashTab[i] = _pScopeNode->hashTab[i];
		}
	}
};

typedef ScopeNode* Scope;

//The operation of the scope
static int hash(string str);
Scope Screate(string Name);
Scope Screate(string Name, Scope pScope);
void Spop();
Scope Stop();
void Spush(string name);
Scope Sfind(string name);

//The operation of the symbol table
void STinsert(string name,int lineNum,int loc,string recType,string dataType);
string STfind(string name);
void STprint();

namespace sym {
	int getArrayBegin(string name, string scope);
	int getNodeNum(string STname, string MEMname, string scope);
	string getIDType(string name, string scope);
	bool getIDIsConst(string name, string scope);
	string getArrayType(string name, string scope);
	string getRecordElementType(string name, string MEMname, string scope);
}
