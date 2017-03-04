#pragma once

XC_BEGIN_NAMESPACE_2(XC, Types)
{
    class TrueTraitType {};
    class FalseTraitType {};

    template <typename T>
    class TypeTraits
    {
    public:
        typedef FalseTraitType HasTrivalDefaultConstruct;
        typedef FalseTraitType HasTrivalCopyConstruct;
        typedef FalseTraitType HasTrivalAssignmentOperator;
        typedef FalseTraitType HasTrivalDestructor;
        typedef FalseTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<char>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<wchar_t>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<unsigned char>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<short>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<unsigned short>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<int>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<unsigned int>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<long>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<unsigned long>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<long long>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<unsigned long long>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<float>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<double>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <> class TypeTraits<long double>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <typename T>
    class TypeTraits<T *>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };

    template <typename T>
    class TypeTraits<const T *>
    {
    public:
        typedef TrueTraitType HasTrivalDefaultConstruct;
        typedef TrueTraitType HasTrivalCopyConstruct;
        typedef TrueTraitType HasTrivalAssignmentOperator;
        typedef TrueTraitType HasTrivalDestructor;
        typedef TrueTraitType IsPlainOldDataType;
    };
} XC_END_NAMESPACE_2;