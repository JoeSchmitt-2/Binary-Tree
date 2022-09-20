/*
 * Joseph Schmitt
 * COP4530
 * Proj4
 */
#ifndef PROJ4_BET_H
#define PROJ4_BET_H
#include <iostream>
#include <stack>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

class BET
{
private:
    struct BinaryNode
    {
        string element;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode( const string & theElement, BinaryNode *lt, BinaryNode *rt )
                : element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode( string && theElement, BinaryNode *lt, BinaryNode *rt)
                : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    BinaryNode *root;
    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t);
    BinaryNode * newNode(string n);
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);

public:
    BET();
    BET(const string postfix);
    BET(const BET&);
    ~BET();
    bool buildFromPostfix(const string postfix);
    const BET & operator=(const BET & rhs);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
    bool isOperator(const string &x);
    bool errorChecking(const vector<string> postfixExpression);
    void tokenize(string const &str, const char delim, vector<string> &out);
};

#endif //PROJ4_BET_H
