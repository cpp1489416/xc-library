#pragma once
#include "XAbstractParseNode.h"
class XConstantParseNode :
    public XAbstractParseNode
{
public:
    XConstantParseNode();
    XConstantParseNode(double value);
    ~XConstantParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

