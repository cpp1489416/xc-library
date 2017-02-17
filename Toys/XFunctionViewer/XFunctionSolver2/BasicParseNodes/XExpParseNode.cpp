#include <cmath>
#include "XExpParseNode.h"
#include "../XBasicParseNodes.h"

using namespace std;

XExpParseNode::XExpParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XExpParseNode::XExpParseNode(XAbstractParseNode *a)
{
    childs = new XAbstractParseNode*[1];
    childs[0] = a;
}

XExpParseNode::~XExpParseNode()
{
    delete childs[0];
    delete[] childs;
}

string XExpParseNode::getName() const
{
    return "exp";
}

string XExpParseNode::getExpression() const
{
    return "exp(" + childs[0]->getExpression() + ")";
}

int XExpParseNode::getCountChilds() const
{
    return 1;
}

void XExpParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    value = exp(a);
}

XAbstractParseNode *XExpParseNode::clone() const
{
    return new XExpParseNode(childs[0]->clone());
}

XAbstractParseNode *XExpParseNode::getDifferentiate() const
{
    return new XMultiplyParseNode(
        new XExpParseNode(childs[0]->clone()),
        childs[0]->getDifferentiate()
    );
}