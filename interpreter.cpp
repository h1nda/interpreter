// interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

//int ShuntingAlgorithm_Test(string expression) {
//    queue<char> q;
//    stack<char> s; // push 
//}

int main()
{
    string test = "55*3-1";
    size_t next_index;
    int test1 = stoi(test,&next_index);
    cout << test1 << " " << test[next_index];

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
