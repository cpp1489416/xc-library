#include "XAbstractParseNode.h"


XAbstractParseNode::XAbstractParseNode()
{
}

XAbstractParseNode::~XAbstractParseNode()
{
}

double XAbstractParseNode::getValue() const
{
    return value;
}

XAbstractParseNode *XAbstractParseNode::getChild(int index) const
{
    return childs[index];
}

void XAbstractParseNode::updateValue()
{
}

XAbstractParseNode *XAbstractParseNode::clone() const
{
    return nullptr;
}

XAbstractParseNode *XAbstractParseNode::getDifferentiate() const
{
    return nullptr;
}

void XAbstractParseNode::setValue(double value)
{
    this->value = value;
}

void XAbstractParseNode::setChild(XAbstractParseNode *rhs, int index)
{
    delete childs[index];
    childs[index] = rhs;
}