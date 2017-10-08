#pragma once
#include "..\XAbstractParseNode.h"

class XSinParseNode :
    public XAbstractParseNode
{
public:
    XSinParseNode();
    XSinParseNode(XAbstractParseNode *a);
    ~XSinParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

