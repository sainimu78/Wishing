#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	class CNoDupPathCollector
	{
	public:
		void Add(const Niflect::CString& path)
		{
			auto ret = m_setAlreadyAdded.insert(path);
			if (ret.second)
				m_vecPath.push_back(*ret.first);
		}
		void AddFromCollector(const CNoDupPathCollector& rhs)
		{
			for (auto& it : rhs.m_vecPath)
			m_vecPath.push_back(it);
		}
		void AddPaths(const Niflect::TArrayNif<Niflect::CString>& vec)
		{
			for (auto& it : vec)
				this->Add(it);
		}

	public:
		Niflect::TArrayNif<Niflect::CString> m_vecPath;

	private:
		Niflect::TSet<Niflect::CString> m_setAlreadyAdded;
	};
}