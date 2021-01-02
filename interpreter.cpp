// interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
//class Operation {
//public:
//    virtual void print() = 0;
//};
//class Operator : public Operation {
//	enum class Priority{ HIGHEST, HIGH, LOW };
//public:
//	char op;
//	Priority p;
//	Operation* left;
//	Operation* right;
//
//	Operator(char op) : op(op) {
//		if (op == '(' || op == ')')
//			p = Priority::HIGHEST;
//		else if (op == '*' || op == '/')
//			p = Priority::HIGH;
//		else if (op == '+' || op == '-')
//			p = Priority::LOW;
//	}
//
//    void print() {
//        cout << op;
//   }
//};
//class Operand : public Operation {
//public:
//	int value; 
//	Operand(int value) : value(value) {  };
//    void print() {
//        cout << value;
//    }
//};

bool Precedence(char op) {
	if (op == '*' || op == '/')
		return 1;
	return 0;
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}
int build_int(string s, size_t fidx, size_t* lidx) {
	int result = 0;
	for (size_t i = fidx; i < s.length(); i++) {
		if (isDigit(s[i])) {
			result = result * 10 + (s[i] - '0');
		}
		else
		{
			*lidx = i;
			return result;

		}

	}
}
////Dijkstra's Shunting Algorithm explanation
void ShuntingAlgorithm_Test(string expr) {
	//    /*Algorithm: whenever we encounter a digit, we run it through build_int to check if it's a multidigit number, 
	//    then we push it onto the queue,
	//    whenever we encounter an operation (*,/,+,-, ()) we push it into the stack
	//    if the top element in the stack has higher precedence than the current one to be pushed, we pop it and enqueue
	//    otherwise we push the current.*/
	stack<char> st; // push 
	//string infix;
	string infix;
	for (int i = 0; i < expr.length(); i++) {

		while (isDigit(expr[i])) {
			infix.push_back(expr[i]);
			i++;
		}
		if (expr[i] == '(') {
			st.push(expr[i]);
			continue;
		}
		else if (expr[i] == ')') {
			while (!st.empty()) {
				if (st.top() == '(') {
					
					st.pop();
					break;
				}
				else {
					infix.push_back(' ');
					infix.push_back(st.top());
					st.pop();
				}
			}
		}
		else if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
			if (st.empty() || st.top() == '(' || Precedence(st.top()) < Precedence(expr[i])) {
				st.push(expr[i]);
			}
			else {
				infix.push_back(' ');
				infix.push_back(st.top());
				st.pop();
				st.push(expr[i]);
			}
		}
		infix.push_back(' ');
	}
	while (!st.empty()) {
		infix.push_back(st.top());
		st.pop();
		infix.push_back(' ');
	}


	//    /*Using a bool as a BODMAS rule we determine precedence:
	//    HIGH (1) are * and /;
	//    LOW (0) are - and +;
	//    If they are of the same precedence we calculate using left associativity.*/
	cout << infix;
}

int main()
{
	string test = "90/5-10*11";
	ShuntingAlgorithm_Test(test);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
