TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../Core/UnitTest.cpp

HEADERS += \
    ../../Core/Containers/XCArray.h \
    ../../Core/Containers/XCList.h \
    ../../Core/Deleted/AVLTree.h \
    ../../Core/Deleted/BinaryTree.h \
    ../../Core/Deleted/List.h \
    ../../Core/Deleted/Map.h \
    ../../Core/Deleted/RedBlackTree.h \
    ../../Core/Deleted/Stack.h \
    ../../Core/Memory/XCAllocators.h \
    ../../Core/Memory/XCConstruts.h \
    ../../Core/Memory/XCInitialized.h \
    ../../Core/Memory/XCUninitializeds.h \
    ../../Core/Pointers/XCAutoPointer.h \
    ../../Core/Tuples/XCTuple.h \
    ../../Core/XCAlgorithm.h \
    ../../Core/XCBasic.h \
    ../../Core/XCContainers.h \
    ../../Core/XCIterators.h \
    ../../Core/XCMemory.h \
    ../../Core/XCPointers.h \
    ../../Core/XCTuples.h \
    ../../Core/XCTypeTraits.h \
    ../../Core/Containers/XCDequeue.h

