#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;
	using namespace Engine;

	class CSomeClass
	{

	};
	using CSomeClass2 = CSomeClass;
	using CSomeClass3 = CSomeClass2;

	struct SSomeStruct
	{

	};
	template <typename T>
	class TSomeClassTpl
	{

	};
	using CSomeClassSpec = TSomeClassTpl<float>;

	template <typename T0, typename T1>
	class TSomeClassTpl2D
	{

	};
	template <typename T0, typename T1>
	using TSomeClassTpl2DAls = TSomeClassTpl2D<T0, T1>;

	template <typename T>
	class TUnary_1D
	{
	};
	template <typename T0, typename T1>
	class TBinary_2D
	{
	};

	using AAA = CSomeClassSpec;
	using BBB = AAA;
	using CCC = BBB;
	typedef CSomeClassSpec DDD;
	typedef AAA EEE;
	using FFF = float;

	template <typename T>
	using TUnaryAls = TUnary_1D<T>;
	using TUnarySpec0 = TUnary_1D<float>;
	using TUnarySpec1 = TUnary_1D<CSomeClassSpec>;
	using TUnarySpec2 = TUnary_1D<AAA>;
	using TUnarySpec3 = TUnary_1D<DDD>;
	using TUnarySpec4 = TUnary_1D<EEE>;
	using TUnarySpec5 = TUnary_1D<CSomeClass>;
	using TUnarySpec6 = TUnary_1D<SSomeStruct>;
	using TUnarySpec7 = TUnary_1D<TSomeClassTpl<float> >;
	using TUnarySpec8 = TUnary_1D<TSomeClassTpl<SSomeStruct> >;
	template <typename T>
	using TUnarySpec9 = TUnary_1D<TSomeClassTpl<T> >;
	using TUnarySpec10 = TUnary_1D<FFF>;
	typedef TUnary_1D<float> CUnarySpec11;
	typedef TUnary_1D<FFF> CUnarySpec12;

	template <typename T0, typename T1>
	using TBinaryAls = TBinary_2D<CSomeClassSpec, TSomeClassTpl2D<T0, T1> >;
	template <typename T0, typename T1>
	using TBinaryAls1 = TBinary_2D<CSomeClassSpec, TSomeClassTpl2DAls<T0, T1> >;
	template <typename T0>
	using TBinaryPartSpec = TBinary_2D<CSomeClassSpec, TSomeClassTpl2D<T0, CSomeClass> >;
	using TBinarySpec = TBinary_2D<CSomeClassSpec, TSomeClassTpl2D<CSomeClass2, CSomeClass> >;

	//NIF_BS() TBindingSetting<TUnary_1D<CSomeClass2>, CSomeClass3, CSomeClass2>;
	//template <typename TMy>
	//NIF_BS() TBindingSetting<TBinaryPartSpec<TMy>, TSomeClassTpl2D<CSomeClass2, CSomeClass> >;
	//template <typename TMy>
	//NIF_BS() TBindingSetting<TBinaryPartSpec<TMy>, TSomeClassTpl2D<CSomeClass3, CSomeClass> >;
	//template <typename TMy, typename T0, typename T1>
	//NIF_BS() TBindingSetting<TBinaryPartSpec<TMy>, TSomeClassTpl2D<T0, T1>, TSomeClassTpl2DAls<T0, T1> >;
	//template <typename TMy, typename T0, typename T1>
	//NIF_BS() TBindingSetting<TBinaryPartSpec<TMy>, TSomeClassTpl2D<T0, T1>, TSomeClassTpl2DAls<CSomeClass3, CSomeClass2> >;
	//template <typename TMy, typename T0, typename T1>
	//NIF_BS() TBindingSetting<TBinaryPartSpec<TMy>, TSomeClassTpl2D<T0, T1>, TSomeClassTpl2DAls<T0, CSomeClass2> >;
	//NIF_BS() TBindingSetting<TUnary_1D<CSomeClass2>, std::vector<bool> >;
	//NIF_BS() TBindingSetting<TUnary_1D<CSomeClass2>, Niflect::TArrayNif<bool> >;

	NIF_BS() TBindingSetting<CBoolAccessor, bool>;
	NIF_BS() TBindingSetting<CFloatAccessor, float>;
	NIF_BS() TBindingSetting<CStringAccessor, Niflect::CString>;
	template <typename TInstance, typename T>
	NIF_BS() TBindingSetting<TStlArrayAccessor<TInstance>, Niflect::TArrayNif<T> >;
	//template <typename TInstance>
	//NIF_BS() TBindingSetting<TStlBitsArrayAccessor<TInstance>, std::vector<bool> >;
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<CCompoundAccessor, std::pair<T0, T1> >;
	template <typename TInstance, typename T0, typename T1>
	NIF_BS() TBindingSetting<TStlMapAccessor<TInstance>, Niflect::TMap<T0, T1>, std::pair<T0, T1> >;

	class CMyClass
	{
	public:
		TUnarySpec1 m_0;
		TUnary_1D<CSomeClassSpec> m_1;
		TBinary_2D<CSomeClassSpec, TSomeClassTpl2D<CSomeClass2, CSomeClass> > m_2;
	};
}