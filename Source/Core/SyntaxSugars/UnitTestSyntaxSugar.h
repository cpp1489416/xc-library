// unit test
#ifndef XC_TEST_CASE_FLAG
#define XC_TEST_CASE_FLAG

#define XC_TEST_CASE(name)                          \
    extern void XCTestCase##name();                 \
    namespace XC_TestCase                           \
    {                                               \
        class TestCaseRunner##name                  \
        {                                           \
        public:                                     \
            TestCaseRunner##name()                  \
            {                                       \
                XCTestCase##name();                 \
            }                                       \
        } gTestCase##name##Instance;                \
    }                                               \
    void XCTestCase##name() 

#define XC_TEST_ASSERT(experssion) do { if (!(experssion)) { throw "error when unit test"; } } while(0)

#endif // XC_TEST_CASE_FLAG
