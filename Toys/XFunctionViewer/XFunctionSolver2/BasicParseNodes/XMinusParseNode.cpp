#include "XMinusParseNode.h"

using namespace std;

XMinusParseNode::XMinusParseNode()
{
    childs = new XAbstractParseNode *[2];
    childs[0] = nullptr;
    childs[1] = nullptr;
}

XMinusParseNode::XMinusParseNode(XAbstractParseNode *a, XAbstractParseNode *b)
{
    childs = new XAbstractParseNode *[2];
    childs[0] = a;
    childs[1] = b;
}

XMinusParseNode::~XMinusParseNode()
{
    delete childs[0];
    delete childs[1];
    delete[] childs;
}

string XMinusParseNode::getName() const
{
    return "-";
}

string XMinusParseNode::getExpression() const
{
    return "(" + childs[0]->getExpression() + " - " + childs[1]->getExpression() + ")";
}

int XMinusParseNode::getCountChilds() const
{
    return 2;
}

void XMinusParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    double b;
    childs[1]->updateValue();
    b = childs[1]->getValue();

    value = a - b;
}

XAbstractParseNode *XMinusParseNode::clone() const
{
    return new XMinusParseNode(childs[0]->clone(), childs[1]->clone());
}

XAbstractParseNode *XMinusParseNode::getDifferentiate() const
{
    return new XMinusParseNode(childs[0]->getDifferentiate(), childs[1]->getDifferentiate());
}