#include "Niflect/Base/NiflectBindingSetting.h"
#include "Niflect/Test/MyField.h"
#include "Niflect/Field/ArrayField.h"
//#include "Niflect/Test/MyClassForGen.h"
#include "Niflect/Field/MapField.h"

namespace TestMyGlobalBindingSetting
{
	using namespace Niflect;
	using namespace MyTestClassScope;
	
	//template <typename TTuple, template <typename ...> class TTemplate>
	//class TTemplateBindingSetting
	//{
	//};

	//using namespace DDDDD;

	template <typename T0, typename T1>
	using TMyPair = std::pair<T0, T1>;
	
	NIF_BS() TBindingSetting<CFloatField, float>;
	NIF_BS() TBindingSetting<CBoolField, bool>;
	NIF_BS() TBindingSetting<CStringField, Niflect::CString>;
	//NIF_BS() TBindingSetting<CStringField2, std::string>;
	template <typename T>
	NIF_BS() TBindingSetting<CArrayField, TArrayNif<T> >;
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<CMapField, TMap<T0, T1>, std::pair<const T0, T1> >;
	template <typename T0, typename T1>
	NIF_BS() TBindingSetting<CPairField, std::pair<const T0, T1> >;
	
	//NIF_BS() TTemplateBindingSetting<CArrayField, TArrayNif>;

	//class SSSS
	//{
	//public:
	//	TTemplateBindingSetting<CArrayField, TArrayNif> m_a;
	//};

	//template <typename Ta0, typename Ta1>
	//class TA
	//{
	//};
	//template <typename Tb0, typename Tb1, typename Tb2>
	//class TB
	//{
	//};
	//
	//template <typename T1, typename T2, typename T3>
	//NIF_BS() TBindingSetting<CArrayField, TB<float, TA<T1, TA<Niflect::TArrayNif<float>, DDDDD::TSSSSSS::MyString> >, T3> >;
}