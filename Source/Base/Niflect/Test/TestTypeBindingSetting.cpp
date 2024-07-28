#include "Niflect/Test/TestTypeBindingSetting.h"
//#include "Niflect/Base/NiflectBindingSetting.h"
////#include "Niflect/Base/NiflectBase.h"
//
//namespace MyStd
//{
//	template <typename T>
//	class TMyArray
//	{
//
//	};
//}
//
//class CMyAccessorBase
//{
//
//};
//
//class CMyAccessor0
//{
//
//};
//
//class CMyAccessor1 : public CMyAccessorBase
//{
//
//};
//
//class CMyAccessor2
//{
//
//};
//
//class CMyAccessor3
//{
//
//};
//
//class CMyAccessorDebug
//{
//public:
//	float m_myMemberFloat;
//};
//
//using namespace Niflect;
//
////NIF_BIND_BEGIN TTypeBinding<float, TAccessorsTuple<bool, int> > NIF_BIND_END;
////NIF_BIND_BEGIN TTypeBinding<bool, TAccessorsTuple<CMyAccessor0, CMyAccessor1, CMyAccessor2, CMyAccessor3> > NIF_BIND_END;
////using namespace MyStd;
////NIF_BIND_BEGIN TTemplateTypeBinding<TMyArray, TAccessorsTuple<CMyAccessor0, CMyAccessor1> > NIF_BIND_END;
//////NIF_BIND_BEGIN TTemplateTypeBinding<TArrayNif, TAccessorsTuple<CMyAccessorDebug> > NIF_BIND_END;
//
//
//namespace SSSSSS
//{
//#define NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C) A##B##C
//#define NIFLECTGENINTERNAL_COMBINE(A,B,C) NIFLECTGENINTERNAL_COMBINE_INNER(A,B,C)
//
//#define NIF_BIND using NIFLECTGENINTERNAL_COMBINE(__NiflectInternal_TypeBinding,_,__LINE__) = 
//	NIF_BIND TBindingSetting<float, TAccessorsTuple<bool, int> >;
//	NIF_BIND TBindingSetting<bool, TAccessorsTuple<CMyAccessor0, CMyAccessor1, CMyAccessor2, CMyAccessor3> >;
//	using namespace MyStd;
//	NIF_BIND TTemplateBindingSetting<TMyArray, TAccessorsTuple<CMyAccessor0, CMyAccessor1> >;
//}