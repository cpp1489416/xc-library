#pragma once
#include <string>
#include <vector>
#include "XBasicParseNodes.h"
#include "XVariableParseNode.h"
#include "XConstantParseNode.h"

class XFunctionParser
{
public:
    XFunctionParser();
    ~XFunctionParser();
    void setSource(std::string source);
    double getFunction(double x = 0.0, double y = 0.0, double z = 0.0);
    XAbstractParseNode * getRoot() const;
    std::string getInfixExpression() const;
    std::string getReversePolishExpression() const;
    XFunctionParser * getDifferentiate(std::string variable);

protected:
    int getPriority(std::string ope);
    void genParseTree();
    void solveSource();
    void solveArr(XAbstractParseNode *t);

    std::string source;
    std::vector<std::string> polishTokenStrings;
    XAbstractParseNode *root;
    std::vector<XAbstractParseNode *> arrX;
    std::vector<XAbstractParseNode *> arrY;
    std::vector<XAbstractParseNode *> arrZ;

private:
    XFunctionParser(XFunctionParser &);
    XFunctionParser operator=(const XFunctionParser &);

    // I don't know what the following functions and
    // variables stand for, maybe will be used future ...
    // void freeRoot(XAbstractParseNode *root);
    // void genTokenStrings();
    // std::string polishString;
    // std::vector<std::string> getPolishTokenString() const;
    // void solvePolish();
};

