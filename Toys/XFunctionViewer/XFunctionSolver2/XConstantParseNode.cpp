#include "XConstantParseNode.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

XConstantParseNode::XConstantParseNode()
{
}

XConstantParseNode::XConstantParseNode(double value)
{
    this->value = value;
}

XConstantParseNode::~XConstantParseNode()
{
}

string XConstantParseNode::getName() const
{
    return "Constant";
}

string XConstantParseNode::getExpression() const
{
    char buffer[20];
    sprintf_s(buffer, "%lf", value);
    string ans = buffer;
    return ans;
}

int XConstantParseNode::getCountChilds() const
{
    return -2;
}

XAbstractParseNode *XConstantParseNode::clone() const
{
    XConstantParseNode *ans = new XConstantParseNode;
    ans->setValue(value);
    return ans;
}

XAbstractParseNode *XConstantParseNode::getDifferentiate() const
{
    XConstantParseNode *ans = new XConstantParseNode;
    ans->value = 0.0;
    return ans;
}


