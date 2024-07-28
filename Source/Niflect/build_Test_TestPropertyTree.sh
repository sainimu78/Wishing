g++ \
-oa -std=c++14 \
-lstdc++ \
-DTEST_FOR_GCC \
-DNIFLECT_API= \
-D_DEBUG=1 \
-I../ \
-I../../../../../../S3Engine \
-I../../../../../../Dependencies/include/ \
Memory/Default/DefaultMemory.cpp \
Test/TestSaveLoad.cpp \
Test/TestModule0.cpp \
