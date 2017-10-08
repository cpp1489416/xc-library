#pragma once
#include "..\XAbstractParseNode.h"

class XMinusParseNode :
    public XAbstractParseNode
{
public:
    XMinusParseNode();
    XMinusParseNode(XAbstractParseNode *a, XAbstractParseNode *b);
    ~XMinusParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

