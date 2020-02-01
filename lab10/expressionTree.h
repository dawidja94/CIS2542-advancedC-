/*
Author:		Dawid Jasionowski
Filename:	expressionTree.h
Date:		11/09/2018
Descr:
Provides a class for a postfix expression tree

*/
#include <iostream>
#include <cstdlib>
#include <cstdio>   
#include <cstring>
#include <stack>
#include <sstream>
#include <iomanip>
using namespace std;

struct expTreeNode
{
	double number;
	char op;
	expTreeNode* left_field;
	expTreeNode* right_field;
};
class expressionTree
{
private:
	
	stack<expTreeNode*> numbers;

	expTreeNode* root;


	void createNode(double num)
	{
		expTreeNode *newNode = new expTreeNode;
		newNode->number = num;
		newNode->left_field = newNode->right_field = nullptr;

		numbers.push(newNode);
	}

	void createNode(char symbol)
	{
		expTreeNode *newNode = new expTreeNode;
		newNode->op = symbol;
		newNode->right_field = numbers.top();
		numbers.pop();
		newNode->left_field = numbers.top();
		numbers.pop();

		numbers.push(newNode);
	}
public:
	
	expressionTree()
	{
		root = nullptr;
	}

	~expressionTree()
	{
		destroySubTree(root);
	}
	void destroySubTree(expTreeNode *nodePtr)
	{
		if (nodePtr)
		{
			if (nodePtr->left_field)
				destroySubTree(nodePtr->left_field);
			if (nodePtr->right_field)
				destroySubTree(nodePtr->right_field);
			delete nodePtr;
		}
	}
	expressionTree(string& exp)
	{
		const char DECIMAL = '.';
		const char DELIMITER = ' ';
		stringstream ss(exp);
		string token;
		double num;
		char sym;

		while (getline(ss, token, DELIMITER))
		{
			if (token[0] == DECIMAL || isdigit(token[0]))
			{
				num = atof(token.c_str());
				createNode(num);
			}
			else
			{
				sym = token[0];
				createNode(sym);
			}
		}
		root = numbers.top();
	}

	expTreeNode* get_root() const
	{
		return root;
	}

};


double evaluate(expTreeNode *nodePtr)
{
	 
	if (!nodePtr->left_field && !nodePtr->right_field)
		return nodePtr->number;

	double leftValue = evaluate(nodePtr->left_field);
	double rightValue = evaluate(nodePtr->right_field);

	if (nodePtr->op == '+')
		return leftValue + rightValue;
	if (nodePtr->op == '-')
		return leftValue - rightValue;
	if (nodePtr->op == '*')
		return leftValue * rightValue;
	return leftValue / rightValue;
	
}
/*
Sample output

					/
						0.25 [leaf]
						0.5 [leaf]
Postfix expression: .5 .25 /

		==> evaluates to 2
		==> correct answer is 2
					*
						8.5 [leaf]
						+
							3.7 [leaf]
							2.5 [leaf]
Postfix expression: 2.5 3.7 + 8.5 *

		==> evaluates to 52.7
		==> correct answer is 52.7
					+
						5 [leaf]
						-
							4 [leaf]
							+
								*
									2 [leaf]
									3.1 [leaf]
								5 [leaf]
Postfix expression: 5 3.1 2 * + 4 - 5 +

		==> evaluates to 12.2
		==> correct answer is 12.2
					/
						5 [leaf]
						+
							*
								5 [leaf]
								347.8 [leaf]
							25 [leaf]
Postfix expression: 25 347.8 5 * + 5 /

		==> evaluates to 352.8
		==> correct answer is 352.8
					/
						3 [leaf]
						2 [leaf]
Postfix expression: 2 3 /

		==> evaluates to 0.666667
		==> correct answer is 0.666667

C:\Users\dawid\source\repos\Project11\Debug\Project11.exe (process 16128) exited with code 0.
Press any key to close this window . . .
*/
#pragma once
