#pragma once
#include "..\XAbstractParseNode.h"

class XCosParseNode :
    public XAbstractParseNode
{
public:
    XCosParseNode();
    XCosParseNode(XAbstractParseNode *a);
    ~XCosParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();

    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

