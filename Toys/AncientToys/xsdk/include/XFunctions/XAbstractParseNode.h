#ifndef XABSTRACTPARSENODE_H
#define XABSTRACTPARSENODE_H
#include <string>

class XAbstractParseNode
{
public:
    XAbstractParseNode();
    virtual ~XAbstractParseNode();
    virtual std::string getName() const = 0;
    virtual std::string getExpression() const = 0;
    virtual int getCountChilds() const = 0;
    virtual XAbstractParseNode * getChild(int index) const;
    virtual double getValue() const;
    virtual XAbstractParseNode *clone() const;
    virtual XAbstractParseNode *getDifferentiate() const;
    virtual void updateValue();
    virtual void setValue(double value);
    virtual void setChild(XAbstractParseNode *rhs, int index);

protected:
    double value;
    XAbstractParseNode * *childs;

    friend class XFunctionParser;
};

#endif

