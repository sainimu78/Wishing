#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	enum class ELogTextType
	{
		Info,
		Warning,
		Error,
	};

	class CLogText
	{
	public:
		CLogText()
			: m_type(ELogTextType::Info)
		{

		}
		CLogText(ELogTextType type)
			: m_type(type)
		{

		}
		ELogTextType m_type;
		Niflect::CString m_text;
	};

	class CGenLogOption
	{
	public:
		CGenLogOption()
			: m_assertOnAddingItem(true)
			, m_printAddingItem(true)
			, m_cacheItems(false)
		{

		}
		bool m_assertOnAddingItem;
		bool m_printAddingItem;
		bool m_cacheItems;
	};

	class CGenLog
	{
	public:
		void Config(const CGenLogOption& opt)
		{
			m_opt = opt;
		}

	public:
		void Info(const Niflect::CString& text);
		void Warning(const Niflect::CString& text);
		void Error(const Niflect::CString& text);

	private:
		CLogText& AllocItem(ELogTextType type);
		void WriteItem(ELogTextType type, const Niflect::CString& text);

	public:
		Niflect::TArrayNif<CLogText> m_vecText;
		CGenLogOption m_opt;
	};

	void GenLogError(CGenLog* log, const Niflect::CString& text);

	void MyLogError(const Niflect::CString& text);
	void MyLogErrorChecked(bool condition, const Niflect::CString& text);
}