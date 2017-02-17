#pragma once

class Vector3D
{
public:
    using Self = Vector3D;

public:
    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);

public:
    float & At(int row) { return mData[row]; }
    float & operator () (int row) { return At(row); }
    float & operator [] (int row) { return At(row); }
    float & GetX() { return mData[0]; }
    float & GetY() { return mData[1]; }
    float & GetZ() { return mData[2]; }
    Self operator - (Self & rhs);
    Self operator + (Self & rhs);
    Self operator * (float rhs);
    Self operator / (float rhs);
    float GetLength();
    void Normalize();

public:
    float mData[3];
};