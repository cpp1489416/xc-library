#pragma once
#include "DWidget.h"

class DLayout :
    public DWidget
{
public:
    DLayout();
    ~DLayout();
    void addWidget(DWidget *widget, int row, int column);

public:

public:
    int countRows;
    int countColumns;
};

class DHLayout : public DLayout
{
public:
    void addWidget(DWidget *widget) {}
};

class DVLayout : public DLayout
{

};

class DGridLayout : public DLayout
{

};

