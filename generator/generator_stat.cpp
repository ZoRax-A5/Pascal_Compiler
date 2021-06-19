#include "generator.h"
#include "generator_result.h"

void VisitorGen::visitASTCompoundStat(ASTCompoundStat* node) {
	node->getASTStatList()->accept(this);
}

void VisitorGen::visitASTStatList(ASTStatList* node) {

	std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		//if (iter != list.begin()) {
		//}
		(*iter)->accept(this);
	}
}

void VisitorGen::visitASTStat(ASTStat* node) {
	/*if (node->getLabel() != "") {
		int label = atoi(node->getLabel().c_str());
		if (this->getCurrentBlock()->labels.count(label) > 0) {
			this->RecordErrorMessage("Duplicated label: " + node->getLabel(), node->get_location_pairs());
		}
		else {
			llvm::Function* func = this->builder.GetInsertBlock()->getParent();
			auto label_block = llvm::BasicBlock::Create(this->context, "label_" + node->getLabel(), func);
			this->builder.CreateBr(label_block);
			this->builder.SetInsertPoint(label_block);
			this->getCurrentBlock()->labels[label] = label_block;
		}
	}
	node->getNonLabelStmt()->Accept(this);*/
	//return nullptr;
}

void VisitorGen::visitASTStatAssign(ASTStatAssign* node) {

	/*if (dest_type->isSimple()) {
		if (!isEqual(dest_type, src_type)) {
			//Type conversions
			if (src_type->isIntegerTy() && dest_type->isFloatingPointTy()) {
				src = this->builder.CreateSIToFP(src, llvm::Type::getFloatTy(this->context));
				this->builder.CreateStore(src, dest_ptr);
				return true;
			}
			return false;
		}
		else {
			this->builder.CreateStore(src, dest_ptr);
			return true;
		}
	}
	else if (dest_type->isStringTy()) {
		this->builder.CreateStore(src, dest_ptr);
		return true;
	}
	else if (dest_type->isArrayTy()) {
		this->builder.CreateStore(src, dest_ptr);
		return true;
		//TODO: implement array assignment
	}
	else if (dest_type->isRecordTy()) {
		this->builder.CreateStore(src, dest_ptr);
		return true;
		//TODO: implement record assignment
	}
	return false;*/


	/*std::shared_ptr<VisitorResult> Generator::VisitASTAssignStmt(ASTAssignStmt* node) {
		std::cout << "assign!" << std::endl;
		auto left = std::static_pointer_cast<ValueResult>(node->getExpr1()->Accept(this));
		auto right = std::static_pointer_cast<ValueResult>(node->getExpr2()->Accept(this));
		if (left == nullptr || right == nullptr) return nullptr;
		if (left->getMem() == nullptr)
			return RecordErrorMessage("Invalid l-value.", node->get_location_pairs());
		if (!genAssign(left->getMem(), left->getType(), right->getValue(), right->getType()))
			return RecordErrorMessage("Can not do assignment between different types.", node->get_location_pairs());
		//return nullptr;*/

	node->getLvalue()->accept(this);

	node->getRvalue()->accept(this);

}

void VisitorGen::visitASTStatGoto(ASTStatGoto* node) {
	auto target_block = this->block_stack.back()->labels[atoi(node->getLabel().c_str())];
	std::cout << atoi(node->getLabel().c_str()) << std::endl;
	this->builder.CreateBr(target_block);
	llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	llvm::BasicBlock* cont_block = llvm::BasicBlock::Create(this->context, "goto_cont", func);
	this->builder.SetInsertPoint(cont_block);
	//return nullptr;
}

void VisitorGen::visitASTStatProc(ASTStatProc* node) {

	ASTFuncCall* ast_func = new ASTFuncCall(node->getId(), node->getExprList());
	auto res = ast_func->Accept(this);
	delete ast_func;
	//return res;

	node->getParamList()->accept(this);

}

void VisitorGen::visitASTStatCondIf(ASTStatCondIf* node) {

	llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	llvm::BasicBlock* then_block = llvm::BasicBlock::Create(this->context, "if_then", func);
	llvm::BasicBlock* else_block = llvm::BasicBlock::Create(this->context, "if_else", func);
	llvm::BasicBlock* cont_block = llvm::BasicBlock::Create(this->context, "if_cont", func);
	auto cond_res = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));
	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
		return RecordErrorMessage("Invalid condition in if statement.", node->get_location_pairs());
	this->builder.CreateCondBr(cond_res->getValue(), then_block, else_block);
	this->builder.SetInsertPoint(then_block);
	node->getStmt()->Accept(this);
	this->builder.CreateBr(cont_block);
	this->builder.SetInsertPoint(else_block);
	if (node->getElseClause() != nullptr) {
		node->getElseClause()->Accept(this);
	}
	this->builder.CreateBr(cont_block);
	this->builder.SetInsertPoint(cont_block);
	//return nullptr;*/

	node->getCondition()->accept(this);

	node->getThenCode()->accept(this);
	if (node->getElseCode() != NULL) {
		//json_stream << ",";
		node->getElseCode()->accept(this);
	}

}

void VisitorGen::visitASTStatIterRepeat(ASTStatIterRepeat* node) {

	/*llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	llvm::BasicBlock* body_block = llvm::BasicBlock::Create(this->context, "repeat_body", func);
	llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(this->context, "repeat_cond", func);
	llvm::BasicBlock* cont_block = llvm::BasicBlock::Create(this->context, "repeat_cont", func);
	this->getCurrentBlock()->loop_breaks.push_back(cont_block);

	this->builder.CreateBr(body_block);
	this->builder.SetInsertPoint(body_block);

	node->getStmtList()->Accept(this);

	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(cond_block);
	auto cond_res = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));

	//#if (!cond_res->getValue()->getType()->isIntegerTy(1))
	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
		return RecordErrorMessage("Invalid condition in repeat statement.", node->get_location_pairs());

	this->builder.CreateCondBr(cond_res->getValue(), cont_block, body_block);
	this->builder.SetInsertPoint(cont_block);*/

	this->getCurrentBlock()->loop_breaks.pop_back();
	//return nullptr;


	node->getRepeatStatList()->accept(this);
	//json_stream << ",";
	node->getRepeatCondition()->accept(this);

}

void VisitorGen::visitASTStatIterWhile(ASTStatIterWhile* node) {

	/*llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(this->context, "while_cond", func);
	llvm::BasicBlock* body_block = llvm::BasicBlock::Create(this->context, "while_body", func);
	llvm::BasicBlock* end_block = llvm::BasicBlock::Create(this->context, "while_end", func);
	this->getCurrentBlock()->loop_breaks.push_back(end_block);

	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(cond_block);

	auto cond_res = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));
	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
		return RecordErrorMessage("Invalid condition in while statement.", node->get_location_pairs());

	this->builder.CreateCondBr(cond_res->getValue(), body_block, end_block);
	this->builder.SetInsertPoint(body_block);
	node->getStmt()->Accept(this);


	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(end_block);

	this->getCurrentBlock()->loop_breaks.pop_back();*/


	node->getRepeatStat()->accept(this);

	node->getRepeatCondition()->accept(this);

}

void VisitorGen::visitASTExpr(ASTExpr* node) {}

void VisitorGen::visitASTExprBinary(ASTExprBinary* node) {

	/*auto l = std::static_pointer_cast<ValueResult>(node->getLExpr()->Accept(this));
	auto r = std::static_pointer_cast<ValueResult>(node->getRExpr()->Accept(this));
	if (l == nullptr || r == nullptr)
		return nullptr;
	//The error has been reported in the sub-node, so we just return.

//semantic check
	ASTBinaryExpr::Oper nowOp = node->getOp();
	PascalType* ret = nullptr;
	if (nowOp == Op(GE) || nowOp == Op(GT) || nowOp == Op(LE) || nowOp == Op(LT) || nowOp == Op(EQUAL) || nowOp == Op(UNEQUAL)) {
		if (!check_cmp(l->getType(), r->getType(), ret))
			return RecordErrorMessage("The type of two side in binary compare expression does not matched.", node->get_location_pairs());
	}

	else if (nowOp == Op(AND) || nowOp == Op(OR)) {
		if (!check_logic(l->getType(), r->getType()))
			return RecordErrorMessage("Both sides of the binary logic expression need to be BOOLEAN type.", node->get_location_pairs());
	}
	else {
		if (!check_arith(l->getType(), r->getType(), ret))
			return RecordErrorMessage("The type of two side in binary arithmetic expression does not matched.", node->get_location_pairs());
	}
	bool is_real = isEqual(ret, REAL_TYPE);
	if (nowOp == ASTBinaryExpr::Oper::REALDIV)
		is_real = true;
	auto L = l->getValue(), R = r->getValue();
	if (is_real) {
		L = this->builder.CreateUIToFP(L, getLLVMType(this->context, REAL_TYPE));
		R = this->builder.CreateUIToFP(R, getLLVMType(this->context, REAL_TYPE));
	}
	switch (nowOp)
	{
	case Op(GE):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGE(L, R, "cmpftmp")
			: this->builder.CreateICmpSGE(L, R, "cmptmp"));
	case Op(GT):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGT(L, R, "cmpftmp")
			: this->builder.CreateICmpSGT(L, R, "cmptmp"));
	case Op(LE):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLE(L, R, "cmpftmp")
			: this->builder.CreateICmpSLE(L, R, "cmptmp"));
	case Op(LT):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLT(L, R, "cmpftmp")
			: this->builder.CreateICmpSLT(L, R, "cmptmp"));
	case Op(EQUAL):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOEQ(L, R, "cmpftmp")
			: this->builder.CreateICmpEQ(L, R, "cmptmp"));
	case Op(UNEQUAL):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpONE(L, R, "cmpftmp")
			: this->builder.CreateICmpNE(L, R, "cmptmp"));
	case Op(PLUS):
		return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFAdd(L, R, "addftmp")
			: this->builder.CreateAdd(L, R, "addtmp"));
	case Op(MINUS):
		return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFSub(L, R, "subftmp")
			: this->builder.CreateSub(L, R, "subtmp"));
	case Op(MUL):
		return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFMul(L, R, "mulftmp")
			: this->builder.CreateMul(L, R, "multmp"));
	case Op(DIV):
		if (is_real) return RecordErrorMessage("The type of two side in div must be INTEGER.", node->get_location_pairs());
		return std::make_shared<ValueResult>(ret, this->builder.CreateSDiv(L, R, "divtmp"));
	case Op(MOD):
		if (is_real) return RecordErrorMessage("The type of two side in mod must be INTEGER.", node->get_location_pairs());
		return std::make_shared<ValueResult>(ret, this->builder.CreateSRem(L, R, "modtmp"));
	case Op(REALDIV):
		return std::make_shared<ValueResult>(REAL_TYPE, this->builder.CreateFDiv(L, R, "divftmp"));
	case Op(OR):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, this->builder.CreateOr(L, R, "ortmp"));
	case Op(AND):
		return std::make_shared<ValueResult>(BOOLEAN_TYPE, this->builder.CreateAnd(L, R, "andtmp"));
	}*/
	//return nullptr;


	node->getOpLeft()->accept(this);

	node->getOpRight()->accept(this);

}

void VisitorGen::visitASTExprUnary(ASTExprUnary* node) {

	/*auto t = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));
	if (t == nullptr) return nullptr;
	if (node->getOp() == ASTUnaryExpr::Oper::NOT) {
		if (!isEqual(t->getType(), BOOLEAN_TYPE))
			return RecordErrorMessage("The type after not must be BOOLEAN.", node->get_location_pairs());
		return std::make_shared<ValueResult>(t->getType(), this->builder.CreateNot(t->getValue(), "nottmp"));
	}
	else if (node->getOp() == ASTUnaryExpr::Oper::SUB) {
		if (isEqual(t->getType(), INT_TYPE) && isEqual(t->getType(), REAL_TYPE))
			return RecordErrorMessage("The type after negative sign must be INTEGER or REAL.", node->get_location_pairs());
		llvm::Type* tp = t->getllvmType();
		llvm::Value* zero = llvm::ConstantInt::get(tp, (uint64_t)0, true);
		if (isEqual(t->getType(), REAL_TYPE))
			//return std::make_shared<ValueResult>(t->getType(), this->builder.CreateFSub(zero, t->getValue(), "negaftmp"));
		else
			//return std::make_shared<ValueResult>(t->getType(), this->builder.CreateSub(zero, t->getValue(), "negatmp"));
	}*/

	node->getOp()->accept(this);
}

void VisitorGen::visitASTExprConst(ASTExprConst* node) {

	//return node->getConstValue()->Accept(this);

	node->getConstValue()->accept(this);
}

void VisitorGen::visitASTExprIdentifier(ASTExprIdentifier* node) {

	/*std::string name = node->getId();
	//std::cout << "ID : " << name << std::endl;
	if (this->getCurrentBlock()->isValue(name)) {
		llvm::Value* mem = this->getCurrentBlock()->named_values[name];
		llvm::Value* value = this->builder.CreateLoad(mem);
		std::cerr << "Get local named value: " << name << std::endl;
		return std::make_shared<ValueResult>(this->getVarType(name), value, mem);
	}
	else if (this->block_stack[0]->isValue(name)) {
		llvm::Value* mem = this->block_stack[0]->named_values[name];
		llvm::Value* value = this->builder.CreateLoad(mem);
		std::cerr << "Get global named value: " << name << std::endl;
		return std::make_shared<ValueResult>(this->block_stack[0]->named_types[name], value, mem);
	}
	else {
		std::cout << "start calling no arg func : " << name << std::endl;
		ASTFuncCall* func_call = new ASTFuncCall(name, nullptr);
		auto ret = func_call->Accept(this);
		std::cout << "finish calling no arg func : " << name << " , return " << (ret == nullptr ? "is" : "is not") << " nullptr" << std::endl;
		if (ret != nullptr) return ret;
		return RecordErrorMessage(name + " is neither a variable nor a no-arg function. Cannot get named value: ", node->get_location_pairs());
	}*/

}