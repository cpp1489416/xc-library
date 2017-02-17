#include "XDivideParseNode.h"
#include "../XBasicParseNodes.h"
#include "../XConstantParseNode.h"

using namespace std;

XDivideParseNode::XDivideParseNode()
{
    childs = new XAbstractParseNode *[2];
    childs[0] = nullptr;
    childs[1] = nullptr;
}

XDivideParseNode::XDivideParseNode(XAbstractParseNode *a, XAbstractParseNode *b)
{
    childs = new XAbstractParseNode *[2];
    childs[0] = a;
    childs[1] = b;
}

XDivideParseNode::~XDivideParseNode()
{
    delete childs[0];
    delete childs[1]; 
    delete[] childs;
}

string XDivideParseNode::getName() const
{
    return "/";
}

string XDivideParseNode::getExpression() const
{
    return "(" + childs[0]->getExpression() + " / " + childs[1]->getExpression() + ")";
}

int XDivideParseNode::getCountChilds() const
{
    return 2;
}

void XDivideParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    double b;
    childs[1]->updateValue();
    b = childs[1]->getValue();

    value = a / b;
}

XAbstractParseNode *XDivideParseNode::clone() const
{
    return new XDivideParseNode(childs[0]->clone(), childs[1]->clone());
}

XAbstractParseNode *XDivideParseNode::getDifferentiate() const
{
    return new XDivideParseNode(
        new XMinusParseNode(
            new XMultiplyParseNode(childs[0]->getDifferentiate(), childs[1]->clone()),
            new XMultiplyParseNode(childs[0]->clone(), childs[1]->getDifferentiate())
        ),
        new XPowerParseNode(childs[1]->clone(), new XConstantParseNode(2))
    );
}