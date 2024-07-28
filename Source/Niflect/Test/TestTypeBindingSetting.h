//#include "Niflect/Base/NiflectBindingSetting.h"
//#include "Niflect/Test/TestDebugArray.h"
//#include "Niflect/Field/ArrayField.h"
//#include "Niflect/Test/MyField.h"
//
//namespace MyStd
//{
//	template <typename T>
//	class TMyArray
//	{
//
//	};
//
//	namespace MySub
//	{
//		template <typename T>
//		class TMySubArray0
//		{
//		public:
//			class CMySubSub
//			{
//			
//			};
//		};
//		template <typename T>
//		class TMySubArray1
//		{
//			
//		};
//
//		class CMyEmbedded0
//		{
//		public:
//			class CMyEmbedded1
//			{
//			};
//		};
//	}
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
//namespace DebugNamespace
//{
//	class CMyAccessorDebug
//	{
//	public:
//		float m_myMemberFloat;
//	};
//
//	namespace DebugSub
//	{
//		class CMySubAccessorDebug
//		{
//		public:
//			float m_myMemberFloat;
//		};
//	}
//}
//
//typedef float MyFloatDef;
//
//namespace TestTypeBindingSetting
//{
//	using namespace Niflect;
//	using namespace MyTestClassScope;
//
//	NIF_BS() TBindingSetting<CFloatField, float>;
//	NIF_BS() TBindingSetting<CBoolField, bool>;
//	NIF_BS() TBindingSetting<MyTestClassScope::MySub::CFieldTestMy, int>;
//	NIF_BS() TBindingSetting<MySub::CFieldTestMy::CSubMy0, double>;
//	NIF_BS() TBindingSetting<MySub::CFieldTestMyNoGen::CSubMy1, unsigned>;
//	NIF_BS() TBindingSetting<MyTestClassScope::MySub::CFieldMyFloatDef, MyFloatDef>;
//	NIF_BS() TBindingSetting<CFieldInt, char>;
//	template <typename T>
//	NIF_BS() TBindingSetting<CArrayField, TestContainer::TMyArrayDebug<T> >;
//	//NIF_BS() TBindingSetting2<MySub::CFieldTestMyTemplate<float>::CSubMy2, TTypeTuple<char> >;//todo: 暂不支持, 见NiflectGen注释"现要求Accessor必须带标记"
//}