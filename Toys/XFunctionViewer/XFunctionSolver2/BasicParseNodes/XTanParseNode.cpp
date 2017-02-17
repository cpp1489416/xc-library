#include <cmath>
#include "XTanParseNode.h"
#include "../XBasicParseNodes.h"

using namespace std;

XTanParseNode::XTanParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XTanParseNode::XTanParseNode(XAbstractParseNode *a)
{
    childs = new XAbstractParseNode *[1];
    childs[0] = a;
}

XTanParseNode::~XTanParseNode()
{
    delete childs[0];
    delete[] childs;
}

string XTanParseNode::getName() const
{
    return "tan";
}

string XTanParseNode::getExpression() const
{
    return "tan(" + childs[0]->getExpression() + ")";
}

int XTanParseNode::getCountChilds() const
{
    return 1;
}

void XTanParseNode::updateValue()
{
    double a;
    childs[0]->updateValue();
    a = childs[0]->getValue();

    value = tan(a);
}

XAbstractParseNode *XTanParseNode::clone() const
{
    return new XTanParseNode(childs[0]->clone());
}

XAbstractParseNode *XTanParseNode::getDifferentiate() const
{
    XDivideParseNode *des = new XDivideParseNode(
        new XSinParseNode(childs[0]->clone()),
        new XCosParseNode(childs[0]->clone())
    );
    XAbstractParseNode *ans = des->getDifferentiate();
    delete des;
    return ans;
}