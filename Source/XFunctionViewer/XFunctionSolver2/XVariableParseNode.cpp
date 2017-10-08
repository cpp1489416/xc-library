#include "XVariableParseNode.h"
#include "XConstantParseNode.h"

#include <cstdlib>
#include <iostream>

using namespace std;

XVariableParseNode::XVariableParseNode()
{
}

XVariableParseNode::~XVariableParseNode()
{
}

string XVariableParseNode::getName() const
{
    return "Variable";
}

string XVariableParseNode::getExpression() const
{
    string str;
    str += (char)index;
    return str;
}

int XVariableParseNode::getCountChilds() const
{
    return -1;
}

XAbstractParseNode *XVariableParseNode::clone() const
{
    XVariableParseNode *ans = new XVariableParseNode;
    ans->value = value;
    ans->index = index;
    ans->differentiateActive = differentiateActive;
    return ans;
}

XAbstractParseNode *XVariableParseNode::getDifferentiate() const
{
    XAbstractParseNode *ans = new XConstantParseNode;
    if (differentiateActive)
    {
        ans->setValue(1.0);
    }
    else
    {
        ans->setValue(0.0);
    }
    return ans;
}