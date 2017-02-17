#include "XFunctionParser.h"
#include <cctype>
#include <stack>

using namespace std;

static    bool isDouble(string &str)
{
    if (isdigit(str[0])
        || str[0] == '-' && isdigit(str[1])
        || str[0] == '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool isVaraible(string &str)
{
    if (str == "x" || str == "y" || str == "z")
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool isOperator(string str)
{
    if (isDouble(str) || isVaraible(str))
    {
        return false;
    }
    else
    {
        return true;
    }
}

XFunctionParser::XFunctionParser()
{
    root = nullptr;
}

XFunctionParser::~XFunctionParser()
{
    delete root;
}

void XFunctionParser::setSource(string source)
{
    this->source = source;
    solveSource();
    genParseTree();
}

int XFunctionParser::getPriority(string ope)
{
    if (ope == "(")
    {
        return -1;
    }
    else if (ope == "+" || ope == "-")
    {
        return 0;
    }
    else if (ope == "*" || ope == "/")
    {
        return 1;
    }
    else if (ope == "~")
    {
        return 200;
    }
    else
    {
        return 3;
    }
}

void XFunctionParser::solveSource()
{
    vector<string> sourceToken;
    int cur = 0;
    while (cur < source.length())
    {
        while (source[cur] == ' ' || source[cur] == ',')
        {
            cur++;
        }
        if (source[cur] == '(' || source[cur] == ')'
            || source[cur] == 'x' || source[cur] == 'y' || source[cur] == 'z'
            || source[cur] == '-'  || source[cur] == '~'
            || source[cur] == '+' || source[cur] == '*' || source[cur] == '/'
            || source[cur] == '^')
        {
            string str;
            str += source[cur];
            sourceToken.push_back(str);
            cur++;
            continue;
        }

        if (isdigit(source[cur]) || source[cur] == '.' || source[cur] == '-')
        {
            string str;
            str += source[cur];
            cur++;
            while (isdigit(source[cur]) || source[cur] == '.')
            {
                str += source[cur];
                cur++;
            }
            sourceToken.push_back(str);
            continue;
        }

        if (isalpha(source[cur]))
        {
            string str;
            while (isalpha(source[cur]))
            {
                str += source[cur];
                cur++;
            }
            sourceToken.push_back(str);
            continue;
        }
    }

    //for (int j = 0; j < sourceToken.size(); j++) {
    //    cout << sourceToken[j] << endl;
    //}

    polishTokenStrings.clear();
    stack<string> stkOpe;
    for (int i = 0; i < sourceToken.size(); i++)
    {
        if (isDouble(sourceToken[i]) || isVaraible(sourceToken[i]))
        {
            polishTokenStrings.push_back(sourceToken[i]);
        }
        else if (sourceToken[i] == "(")
        {
            stkOpe.push("(");
        }
        else if (sourceToken[i] == ")")
        {
            while (stkOpe.top() != "(")
            {
                string ope = stkOpe.top();
                polishTokenStrings.push_back(ope);
                stkOpe.pop();
            }
            stkOpe.pop();
        }
        else
        {
            string sOpe = sourceToken[i];
            while (!stkOpe.empty()
                && getPriority(sOpe) < getPriority(stkOpe.top()))
            {
                string ope = stkOpe.top();
                polishTokenStrings.push_back(ope);
                stkOpe.pop();
            }
            stkOpe.push(sOpe);
        }
    }
    while (!stkOpe.empty())
    {
        polishTokenStrings.push_back(stkOpe.top());
        stkOpe.pop();
    }

    //for (int i = 0; i < polishTokenStrings.size(); i++) {
    //    cout << polishTokenStrings[i] << endl;
    //}
}

void XFunctionParser::genParseTree()
{
    delete root;
    arrX.clear();
    arrY.clear();
    arrZ.clear();
    stack<XAbstractParseNode *> stk;
    for (int i = 0; i < polishTokenStrings.size(); i++)
    {
        string str = polishTokenStrings[i];
        if (str == "x" || str == "y" || str == "z")
        {
            XVariableParseNode *node = new XVariableParseNode;
            node->index = str[0];
            stk.push(node);
            if (str[0] == 'x')
            {
                arrX.push_back(node);
            }
            else if (str[0] == 'y')
            {
                arrY.push_back(node);
            }
            else
            {
                arrZ.push_back(node);
            }
        }
        else if (isdigit(str[0])
            || str[0] == '.'
            || str[0] == '-' && isdigit(str[1]))
        {
            double val = atof(str.c_str());
            XConstantParseNode *node = new XConstantParseNode;
            node->value = val;
            stk.push(node);
        }
        else if (str == "+")
        {
            XPlusParseNode *node = new XPlusParseNode;
            XAbstractParseNode *b = stk.top();
            stk.pop();
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            node->childs[1] = b;
            stk.push(node);
        }
        else if (str == "-")
        {
            XMinusParseNode *node = new XMinusParseNode;
            XAbstractParseNode *b = stk.top();
            stk.pop();
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            node->childs[1] = b;
            stk.push(node);
        }
        else if (str == "*")
        {
            XMultiplyParseNode *node = new XMultiplyParseNode;
            XAbstractParseNode *b = stk.top();
            stk.pop();
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            node->childs[1] = b;
            stk.push(node);
        }
        else if (str == "/")
        {
            XDivideParseNode *node = new XDivideParseNode;
            XAbstractParseNode *b = stk.top();
            stk.pop();
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            node->childs[1] = b;
            stk.push(node);
        }
        else if (str == "^")
        {
            XPowerParseNode *node = new XPowerParseNode;
            XAbstractParseNode *b = stk.top();
            stk.pop();
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            node->childs[1] = b;
            stk.push(node);
        }
        else if (str == "~")
        {
            XNegateParseNode *node = new XNegateParseNode;
            node->childs[0] = stk.top();
            stk.pop();
            stk.push(node);
        }
        else if (str == "sin")
        {
            XSinParseNode *node = new XSinParseNode;
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            stk.push(node);
        }
        else if (str == "cos")
        {
            XCosParseNode *node = new XCosParseNode;
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            stk.push(node);
        }
        else if (str == "tan")
        {
            XTanParseNode *node = new XTanParseNode;
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            stk.push(node);
        }
        else if (str == "exp")
        {
            XExpParseNode *node = new XExpParseNode;
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            stk.push(node);
        }
        else if (str == "ln")
        {
            XLnParseNode *node = new XLnParseNode;
            XAbstractParseNode *a = stk.top();
            stk.pop();
            node->childs[0] = a;
            stk.push(node);
        }
    }
    root = stk.top();
}

double XFunctionParser::getFunction(double x, double y, double z)
{
    for (int i = 0; i < arrX.size(); i++)
    {
        arrX[i]->value = x;
    }

    for (int i = 0; i < arrY.size(); i++)
    {
        arrY[i]->value = y;
    }

    for (int i = 0; i < arrZ.size(); i++)
    {
        arrZ[i]->value = z;
    }

    root->updateValue();
    return root->getValue();
}

void XFunctionParser::solveArr(XAbstractParseNode *r)
{
    if (typeid(*r) == typeid(XVariableParseNode))
    {
        XVariableParseNode *vnd = dynamic_cast<XVariableParseNode *>(r);
        if (vnd->index == 'x')
        {
            arrX.push_back(vnd);
        }
        else if (vnd->index == 'y')
        {
            arrY.push_back(vnd);
        }
        else if (vnd->index == 'z')
        {
            arrZ.push_back(vnd);
        }
        return;
    }
    int ccs = r->getCountChilds();
    for (int i = 0; i < ccs; i++)
    {
        solveArr(r->getChild(i));
    }
}

XFunctionParser * XFunctionParser::getDifferentiate(string variable)
{
    for (int i = 0; i < arrX.size(); i++)
    {
        XVariableParseNode *node = (XVariableParseNode *)arrX[i];
        if (variable == "x")
        {
            node->differentiateActive = true;
        }
        else
        {
            node->differentiateActive = false;
        }
    }
    for (int i = 0; i < arrY.size(); i++)
    {
        XVariableParseNode *node = (XVariableParseNode *)arrY[i];
        if (variable == "y")
        {
            node->differentiateActive = true;
        }
        else
        {
            node->differentiateActive = false;
        }
    }
    for (int i = 0; i < arrZ.size(); i++)
    {
        XVariableParseNode *node = (XVariableParseNode *)arrZ[i];
        if (variable == "z")
        {
            node->differentiateActive = true;
        }
        else
        {
            node->differentiateActive = false;
        }
    }

    XAbstractParseNode *newRoot = root->getDifferentiate();
    XFunctionParser *ans = new XFunctionParser;
    ans->root = newRoot;
    ans->solveArr(newRoot);
    return ans;
}

XAbstractParseNode *XFunctionParser::getRoot() const
{
    return root;
}

string XFunctionParser::getInfixExpression() const
{
    if (root != nullptr)
    {
        return root->getExpression();
    }
    else
    {
        return "IMPOSSIBLE";
    }
}

string XFunctionParser::getReversePolishExpression() const
{
    if (polishTokenStrings.empty())
    {
        return "IMPOSSIBLE";
    }
    string ans;
    ans += polishTokenStrings[0];
    for (int i = 1; i < polishTokenStrings.size(); i++)
    {
        ans += " " + polishTokenStrings[i];
    }
    return ans;
}

// I think the following functions will never be used again, 
// just for me to look back on ...
//
//void XFunctionParser::freeRoot(XAbstractParseNode *r)
//{
//    if (r == nullptr) {
//        return;
//    }
//    int cnt = r->getCountChilds();
//    for (int i = 0; i < cnt; i++) {
//        freeRoot(r->childs[i]);
//        delete root->childs[i];
//    }
//    delete r;
//    r = nullptr;
//}
//
//void XFunctionParser::genTokenStrings()
//{
//    polishTokenStrings.clear();
//    int cur = 0;
//    while (cur < polishString.size()) {
//        while (polishString[cur] == ' ') {
//            cur++;
//        }
//        string str;
//        while (polishString[cur] != ' ' && polishString[cur] != '\0') {
//            str += polishString[cur];
//            cur++;
//        }
//        polishTokenStrings.push_back(str);
//    }
//}
//
//vector<string> XFunctionParser::getPolishTokenString() const
//{
//    return polishTokenStrings;
//}
//
//string XFunctionParser::getInfixExpression(XAbstractParseNode *r) const
//{
//    if (r == nullptr) {
//        return "";
//    }
//    if (r->getCountChilds() < 0) {
//        XVariableParseNode *rv = (XVariableParseNode *)(r);
//        string str = "";
//        str += rv->index;
//        return str;
//    } else {
//        XAbstractParseNode *rb = (XAbstractParseNode *)r;
//        if (rb->getCountChilds() == 2) {
//            return "(" + (string)getInfixExpression(rb->childs[0]) + " "
//                + (string)rb->getName() + " "
//                + (string)getInfixExpression(rb->childs[1]) + ")";
//        } else if (rb->getCountChilds() == 1) {
//            return (string)rb->getName() + "("
//                + getInfixExpression(rb->childs[0]) + ")";
//        }
//    }
//}
