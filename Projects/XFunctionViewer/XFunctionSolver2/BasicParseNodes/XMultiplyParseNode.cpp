#include "XMultiplyParseNode.h"
#include "XPlusParseNode.h"

using namespace std;

XMultiplyParseNode::XMultiplyParseNode()
{
    childs = new XAbstractParseNode *[2];
    childs[0] = nullptr;
    childs[1] = nullptr;
}

XMultiplyParseNode::XMultiplyParseNode(XAbstractParseNode *a, XAbstractParseNode *b)
{
    childs = new XAbstractParseNode *[2];
    childs[0] = a;
    childs[1] = b;
}

XMultiplyParseNode::~XMultiplyParseNode()
{
    delete childs[0];
    delete childs[1];
    delete[] childs;
}

string XMultiplyParseNode::getName() const
{
    return "*";
}

string XMultiplyParseNode::getExpression() const
{
    return "(" + childs[0]->getExpression() + " * " + childs[1]->getExpression() + ")";
}

int XMultiplyParseNode::getCountChilds() const
{
    return 2;
}

void XMultiplyParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    double b;
    childs[1]->updateValue();
    b = childs[1]->getValue();

    value = a * b;
}

XAbstractParseNode *XMultiplyParseNode::clone() const
{
    XAbstractParseNode *a = childs[0]->clone();
    XAbstractParseNode *b = childs[1]->clone();
    XMultiplyParseNode *ans = new XMultiplyParseNode;
    ans->setChild(a, 0);
    ans->setChild(b, 1);
    return ans;
}

XAbstractParseNode *XMultiplyParseNode::getDifferentiate() const
{
    return new XPlusParseNode(
        new XMultiplyParseNode(childs[0]->getDifferentiate(), childs[1]->clone()),
        new XMultiplyParseNode(childs[0]->clone(), childs[1]->getDifferentiate())
    );
}