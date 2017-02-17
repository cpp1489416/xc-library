#include "XNegateParseNode.h"

XNegateParseNode::XNegateParseNode()
{
    childs = new XAbstractParseNode *[1];
    childs[0] = nullptr;
}

XNegateParseNode::XNegateParseNode(XAbstractParseNode * a)
{
    childs = new XAbstractParseNode *[1];
    childs[0] = a;
}


XNegateParseNode::~XNegateParseNode()
{
    delete childs[0];
    delete childs;
}

std::string XNegateParseNode::getName() const
{
    return "~";
}

std::string XNegateParseNode::getExpression() const
{
    return "~" + childs[0]->getExpression();
}

int XNegateParseNode::getCountChilds() const
{
    return 1;
}

void XNegateParseNode::updateValue()
{
    childs[0]->updateValue();
    value = -1.0 * childs[0]->getValue();
}

XAbstractParseNode * XNegateParseNode::clone() const
{
    return new XNegateParseNode(childs[0]->clone());
}

XAbstractParseNode * XNegateParseNode::getDifferentiate() const
{
    return new XNegateParseNode(
        childs[0]->getDifferentiate()
    );
}
