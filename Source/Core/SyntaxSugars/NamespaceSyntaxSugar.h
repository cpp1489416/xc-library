#pragma once 

// easy namesapce
#ifndef XC_NAMESPACE_FLAG
#define XC_NAMESPACE_FLAG

#define XC_BEGIN_NAMESPACE(name) namespace name 
#define XC_END_NAMESPACE 

#define XC_BEGIN_NAMESPACE_1(name) namespace name 
#define XC_END_NAMESPACE_1

#define XC_BEGIN_NAMESPACE_2(name1, name2) namespace name1 { namespace name2  
#define XC_END_NAMESPACE_2 }

#define XC_BEGIN_NAMESPACE_3(name1, name2, name3) namespace name1 { namespace name2 { namespace name3 
#define XC_END_NAMESPACE_3 } }

#define XC_BEGIN_NAMESPACE_4(name1, name2, name3, name4) namespace name1 { namespace name2 { namespace name3 {namespace name4 
#define XC_END_NAMESPACE_4 } } }

#define XC_BEGIN_NAMESPACE_5(name1, name2, name3, name4, name5) namespace name1 { namespace name2 { namespace name3 { namespace name4 { namespace name5 {
#define XC_END_NAMESPACE_5 } } } }

#endif // XC_NAMESPACE_FLAG

