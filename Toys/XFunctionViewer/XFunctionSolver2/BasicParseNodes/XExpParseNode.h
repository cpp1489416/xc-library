#pragma once
#include "..\XAbstractParseNode.h"

class XExpParseNode :
    public XAbstractParseNode
{
public:
    XExpParseNode();
    XExpParseNode(XAbstractParseNode *a);
    ~XExpParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

