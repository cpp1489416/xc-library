#include "XPlusParseNode.h"

using namespace std;

XPlusParseNode::XPlusParseNode()
{
    childs = new XAbstractParseNode *[2];
    childs[0] = nullptr;
    childs[1] = nullptr;
}

XPlusParseNode::XPlusParseNode(XAbstractParseNode *a, XAbstractParseNode *b)
{
    childs = new XAbstractParseNode *[2];
    childs[0] = a;
    childs[1] = b;
}

XPlusParseNode::~XPlusParseNode()
{
    delete childs[0];
    delete childs[1];
    delete[] childs;
}

string XPlusParseNode::getName() const
{
    return "+";
}

string XPlusParseNode::getExpression() const
{
    return "(" + childs[0]->getExpression() + " + " + childs[1]->getExpression() + ")";
}

int XPlusParseNode::getCountChilds() const
{
    return 2;
}

void XPlusParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();
    
    double b;
    childs[1]->updateValue();
    b = childs[1]->getValue();

    value = a + b;
}

XAbstractParseNode *XPlusParseNode::clone() const
{
    XPlusParseNode *ans = new XPlusParseNode(childs[0]->clone(), childs[1]->clone());
    return ans;
}

XAbstractParseNode *XPlusParseNode::getDifferentiate() const
{
    XAbstractParseNode *a = childs[0]->getDifferentiate();
    XAbstractParseNode *b = childs[1]->getDifferentiate();
    XPlusParseNode *ans = new XPlusParseNode;
    ans->childs[0] = a;
    ans->childs[1] = b;
    return ans;
}