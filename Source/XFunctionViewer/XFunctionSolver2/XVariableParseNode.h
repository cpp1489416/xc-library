#pragma once
#include "XAbstractParseNode.h"

class XVariableParseNode :
    public XAbstractParseNode
{
public:
    XVariableParseNode();
    ~XVariableParseNode();
    virtual std::string getName() const;
    virtual std::string getExpression() const;
    virtual int getCountChilds() const;
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
    inline char getIndex() const
    {
        return index;
    }

protected:
    char index;
    bool differentiateActive;

    friend class XFunctionParser;
};

