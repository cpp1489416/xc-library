#include <cmath>
#include "XCosParseNode.h"
#include "../XBasicParseNodes.h"
#include "../XConstantParseNode.h"

using namespace std;

XCosParseNode::XCosParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XCosParseNode::XCosParseNode(XAbstractParseNode *a)
{
    childs = new XAbstractParseNode *[1];
    childs[0] = a;
}

XCosParseNode::~XCosParseNode()
{
    delete childs[0];
    delete[] childs;
}

string XCosParseNode::getName() const
{
    return "cos";
}

string XCosParseNode::getExpression() const
{
    return "cos(" + childs[0]->getExpression() + ")";
}

int XCosParseNode::getCountChilds() const
{
    return 1;
}

void XCosParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();
    value = cos(a);
}

XAbstractParseNode *XCosParseNode::clone() const
{
    return new XCosParseNode(childs[0]->clone());
}

XAbstractParseNode *XCosParseNode::getDifferentiate() const
{
    XAbstractParseNode *ori = childs[0]->clone();
    XSinParseNode *sin = new XSinParseNode;
    sin->setChild(ori, 0);
    XMinusParseNode *minus = new XMinusParseNode;
    XConstantParseNode *zero = new XConstantParseNode;
    zero->setValue(0.0);
    minus->setChild(zero, 0);
    minus->setChild(sin, 1);
    XAbstractParseNode *diffOri = childs[0]->getDifferentiate();
    XMultiplyParseNode *ans = new XMultiplyParseNode;
    ans->setChild(minus, 0);
    ans->setChild(diffOri, 1);
    return ans;
}