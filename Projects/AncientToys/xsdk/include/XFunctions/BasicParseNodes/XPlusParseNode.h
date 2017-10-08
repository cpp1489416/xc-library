#pragma once
#include "..\XAbstractParseNode.h"

class XPlusParseNode :
    public XAbstractParseNode
{
public:
    XPlusParseNode();
    XPlusParseNode(XAbstractParseNode *a, XAbstractParseNode *b);
    ~XPlusParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

