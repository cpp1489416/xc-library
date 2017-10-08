#pragma once

class Matrix4x4
{
public :
    Matrix4x4();
    float & operator () (int row, int column);

public:
    static Matrix4x4 GetIdentity();

public:
    const void * GetData() const { return mData; }
    void SetToIdentity();
    void Rotate();
    void Scale();

private:
    float mData[16];
};