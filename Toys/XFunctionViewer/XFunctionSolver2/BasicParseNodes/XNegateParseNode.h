#pragma once
#include "..\XAbstractParseNode.h"
#include <string>

class XNegateParseNode :
    public XAbstractParseNode
{
public:
    XNegateParseNode();
    XNegateParseNode(XAbstractParseNode *a);
    virtual ~XNegateParseNode();
    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;

protected:

};

