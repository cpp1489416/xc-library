#include <cmath>
#include "XLnParseNode.h"
#include "../XBasicParseNodes.h"
#include "../XConstantParseNode.h"

using namespace std;

XLnParseNode::XLnParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XLnParseNode::XLnParseNode(XAbstractParseNode *a)
{
    childs = new XAbstractParseNode *[1];
    childs[0] = a;
}

XLnParseNode::~XLnParseNode()
{
    delete childs[0];
    delete[] childs;
}

string XLnParseNode::getName() const
{
    return "tan";
}

string XLnParseNode::getExpression() const
{
    return "ln(" + childs[0]->getExpression() + ")";
}

int XLnParseNode::getCountChilds() const
{
    return 1;
}

void XLnParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    value = log(a);
}

XAbstractParseNode * XLnParseNode::clone() const
{
    return new XLnParseNode(childs[0]->clone());
}

XAbstractParseNode * XLnParseNode::getDifferentiate() const
{
    return new XMultiplyParseNode(
        new XDivideParseNode(
            new XConstantParseNode(1),
            childs[0]->clone()
        ),
        childs[0]->getDifferentiate()
    );
}