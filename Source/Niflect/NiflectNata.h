#pragma once

namespace Niflect
{
	//Native Meta
	class CNata;
	using CSharedNata = TSharedPtr<CNata>;
	class CNata
	{
		template <typename TNata>
		friend CSharedNata MakeDerivedNata(const TNata& derived);

	private:
		virtual bool _DebugFuncForDynamicCast() const { return true; }//仅为动态检查类型避免错误, 如已定义非调试用的virtual函数则可移除, 备注: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 
	};

	template <typename TNata>
	static CSharedNata MakeDerivedNata(const TNata& derived)
	{
		ASSERT(derived._DebugFuncForDynamicCast());//检查是否以 CNata 为基类
		return Niflect::MakeShared<TNata>(derived);
	}
}