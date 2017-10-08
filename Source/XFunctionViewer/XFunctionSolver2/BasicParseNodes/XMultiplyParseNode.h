#pragma once
#include "..\XAbstractParseNode.h"

class XMultiplyParseNode :
    public XAbstractParseNode
{
public:
    XMultiplyParseNode();
    XMultiplyParseNode(XAbstractParseNode *a, XAbstractParseNode *b);
    ~XMultiplyParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

