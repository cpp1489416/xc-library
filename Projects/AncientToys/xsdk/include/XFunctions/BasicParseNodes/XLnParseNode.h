#pragma once
#include "..\XAbstractParseNode.h"

class XLnParseNode :
    public XAbstractParseNode
{
public:
    XLnParseNode();
    XLnParseNode(XAbstractParseNode *a);
    ~XLnParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

