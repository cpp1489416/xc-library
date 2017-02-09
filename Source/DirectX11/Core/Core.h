#pragma once

#ifndef XC_DIRECTX11_CORE_CORE_H
#define XC_DIRECTX11_CORE_CORE_H

// easy namesapce
#ifndef XC_NAMESPACE_FLAG
#define XC_NAMESPACE_FLAG

#define XC_BEGIN_NAMESPACE(name) namespace name {
#define XC_END_NAMESPACE }

#define XC_BEGIN_NAMESPACE_3(name1, name2, name3) namespace name1 { namespace name2 { namespace name3 {
#define XC_END_NAMESPACE_3 }}}

#endif // XC_NAMESPACE_FLAG

// unit test
#ifndef XC_TEST_CASE_FLAG
#define XC_TEST_CASE_FLAG

#define XC_TEST_CASE(name)                          \
    extern void XCTestCase##name();                \
    namespace XC_TestCase                       \
    {                                          \
        class TestCaseRunner##name              \
        {                                        \
        public:                                 \
            TestCaseRunner##name()               \
            {                                   \
                XCTestCase##name();                  \
            }                                       \
        } gTestCase##name##Instance;                    \
    }                                                 \
    void XCTestCase##name() 

#define XC_TEST_ASSERT(experssion) do { if (!(experssion)) { throw "error when unit test"; } } while(0)

#endif // XC_TEST_CASE_FLAG


#endif // XC_DIRECTX11_CORE_CORE_H
