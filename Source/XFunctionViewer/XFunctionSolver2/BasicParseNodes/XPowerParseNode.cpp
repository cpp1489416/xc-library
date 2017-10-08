#include <cmath>
#include "XPowerParseNode.h"
#include "../XBasicParseNodes.h"
#include "../XConstantParseNode.h"

using namespace std;

XPowerParseNode::XPowerParseNode()
{
    childs = new XAbstractParseNode *[2];
    childs[0] = nullptr;
    childs[1] = nullptr;
}

XPowerParseNode::XPowerParseNode(XAbstractParseNode *a, XAbstractParseNode *b)
{
    childs = new XAbstractParseNode *[2];
    childs[0] = a;
    childs[1] = b;
}

XPowerParseNode::~XPowerParseNode()
{
    delete childs[0];
    delete childs[1];
    delete[] childs;
}

string XPowerParseNode::getName() const
{
    return "^";
}

string XPowerParseNode::getExpression() const
{
    return "(" + childs[0]->getExpression() + " ^ " + childs[1]->getExpression() + ")";
}

int XPowerParseNode::getCountChilds() const
{
    return 2;
}

void XPowerParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    double b;
    childs[1]->updateValue();
    b = childs[1]->getValue();

    value = pow(a, b);
}

XAbstractParseNode *XPowerParseNode::clone() const
{
    return new XPowerParseNode(childs[0]->clone(), childs[1]->clone());
}

XAbstractParseNode *XPowerParseNode::getDifferentiate() const
{
    XAbstractParseNode *baser = new XMultiplyParseNode(
        childs[1]->clone(),
        new XLnParseNode(childs[0]->clone())
    );

    return new XMultiplyParseNode(
        new XExpParseNode(baser),
        baser->getDifferentiate()
    );
}