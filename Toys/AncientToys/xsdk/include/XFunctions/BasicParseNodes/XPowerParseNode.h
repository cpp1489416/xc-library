#pragma once
#include "..\XAbstractParseNode.h"

class XPowerParseNode :
    public XAbstractParseNode
{
public:
    XPowerParseNode();
    XPowerParseNode(XAbstractParseNode *a, XAbstractParseNode *b);
    ~XPowerParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

