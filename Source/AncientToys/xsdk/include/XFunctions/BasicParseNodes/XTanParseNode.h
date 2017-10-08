#pragma once
#include "..\XAbstractParseNode.h"

class XTanParseNode :
    public XAbstractParseNode
{
public:
    XTanParseNode();
    XTanParseNode(XAbstractParseNode *a); 
    ~XTanParseNode();

    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual void updateValue();
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
};

