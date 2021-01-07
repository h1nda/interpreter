#pragma once //DEL
#include "SymbolTable.hpp" //takes the ast then traverses/interprets/evaluates it

class Interpreter {
public:
	SymbolTable vars;
	SymbolTable funcs;
public:
	int Evaluate(Node* root) {
		if (root == nullptr)
			return 0;
		switch (root->data.type) {
		case TokenTypes::VAR:
			return vars.Get(root->data);
		case TokenTypes::ASSIGN:
			vars.Insert(root->left->data, Evaluate(root->right));
		case TokenTypes::NUMBER:
			return root->data.value;
		case TokenTypes::PRINT:
			std::cout << Evaluate(root->left);
		case TokenTypes::MULT:
			return Evaluate(root->left) * Evaluate(root->right);
		case TokenTypes::DIV:
			return Evaluate(root->left) / Evaluate(root->right);
		case TokenTypes::MOD:
			return Evaluate(root->left) % Evaluate(root->right);
		case TokenTypes::ADD:
			return Evaluate(root->left) + Evaluate(root->right);
		case TokenTypes::SUB:
			return Evaluate(root->left) - Evaluate(root->right);
		case TokenTypes::BLOCK:
			Evaluate(root->left);
			Evaluate(root->right);
		}
	}
};
