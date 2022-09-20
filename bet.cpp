#include "bet.h"
//print to the standard output the corresponding infix expression
void BET::printInfixExpression(BET::BinaryNode *n)
{
    if( n == nullptr )
        return;

    if( isOperator(n->element))
        cout << "( ";

    printInfixExpression(n->left);
    cout << n->element << " ";
    printInfixExpression(n->right);

    if( isOperator(n->element) )
        cout << " ) ";
}
//delete all nodes in the subtree pointed to by t
void BET::makeEmpty(BET::BinaryNode *&t)
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}
//clone all nodes in the subtree pointed to by t
BET::BinaryNode *BET::clone(BET::BinaryNode *t)
{
    if( t == nullptr )
        return nullptr;
    else
        return new BinaryNode{ t->element, clone( t->left ), clone( t->right )};
}
//print to the standard output the corresponding postfix expression
void BET::printPostfixExpression(BET::BinaryNode *n)
{
    if( n == nullptr )
        return;
    else{
        printPostfixExpression( n->left );
        printPostfixExpression( n->right );
        cout << n->element << " ";
    }
}
//return the number of nodes in the subtree pointed to by t
size_t BET::size(BET::BinaryNode *t)
{
    if( t == NULL )
        return 0;
    else
        return( size( t->left ) + 1 + size( t->right ));
}
//return the number of leaf nodes in the subtree pointed to by t
size_t BET::leaf_nodes(BET::BinaryNode *t)
{
    if( t == NULL )
        return 0;
    if( t->left == NULL && t->right == NULL )
        return 1;
    else
        return leaf_nodes( t->left ) + leaf_nodes( t->right );
}
//default zero-param constructor
BET::BET() : root{ nullptr } { }
//one param constructor, where param "postfix" is
//a string containing a postfix expression
BET::BET(string postfix) : root{ nullptr }
{
    buildFromPostfix(postfix);
}
//copy constructor
BET::BET(const BET & rhs) : root{ nullptr }
{
    root = clone( rhs.root );
}
//destructor
BET::~BET()
{
    makeEmpty( root );
}
//creates a new node
BET::BinaryNode *BET::newNode(string n)
{
    BinaryNode * temp;
    temp->left = temp->right = nullptr;
    temp->element = n;
    return temp;
}
//separates the string(infix expression) into tokens in a vector
void BET::tokenize(string const &str, const char delim, vector<string> &out)
{
    size_t start;
    size_t end = 0;
    while((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
//param "postfix" is string containing postfix expression
//If the tree contains nodes before function is called
//the existing nodes will be deleted
bool BET::buildFromPostfix( const string postfix )
{
    string temp = postfix;
    stack<BET::BinaryNode*> st;
    vector<string> pf;
    tokenize(temp, ' ', pf);

    while(!errorChecking(pf))
    {
        cout << "Enter the first postfix expression: ";
        getline(cin, temp);
        pf.clear();
        buildFromPostfix(temp);
        tokenize(temp, ' ', pf);
    }


    for(int i = 0; i < pf.size(); i++)
    {
        if(isOperator(pf.at(i)))
        {
            BinaryNode * e = st.top(); st.pop();
            BinaryNode * t1 = st.top(); st.pop();
            BinaryNode * t2 = new BinaryNode(pf.at(i), t1, e);

            st.push(t2);
        }
        else if(!isOperator(pf.at(i)))
        {
            st.push(new BinaryNode(pf.at(i),nullptr, nullptr));
        }
    }
    root = st.top();
    return true;
}
//assignment operator
const BET &BET::operator=( const BET & rhs )
{
    root = clone( rhs.root );
    return *this;
}
//calls private version
void BET::printInfixExpression()
{
    printInfixExpression( root );
    cout << endl;
}
//calls private version
void BET::printPostfixExpression()
{
    printPostfixExpression( root );
    cout << endl;
}
//calls private version
size_t BET::size()
{
    return size( root );
}
//calls private version
size_t BET::leaf_nodes()
{
    return leaf_nodes( root );
}
//returns true if empty
bool BET::empty()
{
    return ( root == nullptr );
}
//checks for operator
bool BET::isOperator(const string &x)
{
    return x == "*" || x == "-" || x == "+" || x == "/";
}
//error checking
bool BET::errorChecking(const vector<string> postfixExpression)
{
    bool noErrors = true;
    int s = postfixExpression.size();
    //if size is too small its an error
    if(postfixExpression.size() < 3)
        noErrors = false;
    //if an operator is input before the third index its an error
    for(int i = 0; i < 2; i++)
    {
        if(isOperator(postfixExpression.at(i)))
        {
            noErrors = false;
        }
    }
    //if the expression is divisible by two its an error
    //because every operand needs an operator
    if(postfixExpression.size() % 2 == 0)
        noErrors = false;
    //if final string token is not operator its an error
    if(!isOperator(postfixExpression.at(s - 1)))
        noErrors = false;
    //if errors were flagged output error message
    if( noErrors == false )
    {
        cout << "Invalid entry. Check spacing/operators/operands/parenthesis and try again" << endl;
        return false;
    }
    else
        return true;
}
