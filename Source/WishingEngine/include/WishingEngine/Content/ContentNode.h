#pragma once
#include "Niflect/Base/String.h"
#include "Niflect/Base/SharedPtr.h"
#include "Niflect/Base/Array.h"

namespace Wishing
{
	class CContentNode2
	{
	public:
		CContentNode2();

	public:
		void Init(const Niflect::CString& name, CContentNode2* parent);

	private:
		Niflect::CString m_name;
		CContentNode2* m_parent;
	};
	//using CSharedContentNode2 = Niflect::TSharedPtr<CContentNode2>;

	class CContentFileNode2 : public CContentNode2
	{
		typedef CContentNode2 inherited;
	};
	using CSharedContentFileNode2 = Niflect::TSharedPtr<CContentFileNode2>;

	class CContentDirNode2 : public CContentNode2
	{
		typedef CContentNode2 inherited;
	public:

	private:
		Niflect::TArray<CContentNode2*> m_vecFileNode;
		Niflect::TArray<CContentDirNode2*> m_vecDirNode;
	};
	using CSharedContentDirNode2 = Niflect::TSharedPtr<CContentDirNode2>;
}