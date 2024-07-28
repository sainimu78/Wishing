#include "Niflect/Test/TestTypesHeaderForGen0.h"
#include "Niflect/Test/TestTypesHeaderForGen2.h"

namespace TestTypesForGen
{
	CMyBase0::CMyBase0()
		//: m_memberBasePointer_3(NULL)
		//, m_memberBase_pointer_2(NULL)
		//, m_memberBase_pointer_4(NULL)
	{
	}	
	float CMyBase0::GetFromPointer() const
	{
		return NULL;
		//return m_memberBasePointer_3->m_member2_0_Float_1;
	}
}

namespace TestTypesScope0ForGen
{
	namespace TestTypesScope1ForGen
	{
		CMyClassForGen0_5::CMyClassForGen0_5()
			: m_member0_5_Float_0(456.0f)
		{
		}
	}
}