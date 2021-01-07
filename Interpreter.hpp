#pragma once //DEL
#include "AST.hpp" //takes the ast then traverses/interprets/evaluates it

class Interpreter {

public:
	int Evaluate(Node* root) {
		switch (root->data.type)
		{
		case TokenTypes::Assignment:
		case TokenTypes::Number:
			return root->data.value;
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

		}
	}
};
