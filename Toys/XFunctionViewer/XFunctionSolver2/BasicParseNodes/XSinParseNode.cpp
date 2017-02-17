#include <cmath>
#include "XSinParseNode.h"
#include "../XBasicParseNodes.h"

using namespace std;

XSinParseNode::XSinParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XSinParseNode::XSinParseNode(XAbstractParseNode *a)
{
    childs = new XAbstractParseNode *[1];
    childs[0] = a;
}

XSinParseNode::~XSinParseNode()
{
   delete (childs[0]);
   delete[] childs;
}

string XSinParseNode::getName() const
{
    return "sin";
}

string XSinParseNode::getExpression() const
{
    return "sin(" + childs[0]->getExpression() + ")";
}

int XSinParseNode::getCountChilds() const
{
    return 1;
}

void XSinParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    value = sin(a);
}

XAbstractParseNode *XSinParseNode::clone() const
{
    return new XSinParseNode(childs[0]->clone());
}

XAbstractParseNode *XSinParseNode::getDifferentiate() const
{
    return new XMultiplyParseNode(
        new XCosParseNode(childs[0]->clone()),
        childs[0]->getDifferentiate()
    );
}