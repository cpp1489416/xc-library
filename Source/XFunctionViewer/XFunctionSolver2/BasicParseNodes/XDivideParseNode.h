#pragma once
#include "..\XAbstractParseNode.h"

class XDivideParseNode :
    public XAbstractParseNode
{
public:
    XDivideParseNode();
    XDivideParseNode(XAbstractParseNode *a, XAbstractParseNode *b);
    ~XDivideParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

