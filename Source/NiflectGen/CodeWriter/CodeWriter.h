#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	using CCodeLines = Niflect::TArrayNif<Niflect::CString>;
	
	namespace EscapeChar
	{
		static const char* NewLine = "\n";
		static const char* EmptyLine = "";
	}

	class CWritingHeaderSearchPaths
	{
	public:
		Niflect::TArrayNif<Niflect::CString> m_vecForRegularConversion;//header search paths for regular header file path conversion at writing code stage
		Niflect::TArrayNif<Niflect::CString> m_vecForGenTimeConversion;//header search paths for bypass header file path conversion at writing code stage
	};

	class CCodeWriterRef
	{
	public:
		CCodeWriterRef(Niflect::CString& code)
			: m_code(code)
		{

		}

	public:
		void WriteLine(const Niflect::CString& line)
		{
			m_code += line + EscapeChar::NewLine;
		}
		void WriteLines(const CCodeLines& lines)
		{
			for (auto& it : lines)
				m_code += it + EscapeChar::NewLine;
		}
		void Write(const Niflect::CString& code)
		{
			m_code += code;
		}

	public:
		Niflect::CString& m_code;
	};

	class CCodeWriter : public CCodeWriterRef
	{
		typedef CCodeWriterRef inherited;
	public:
		CCodeWriter()
			: inherited(m_stm)
		{
		}

	private:
		Niflect::CString m_stm;
	};

	static void DebugPrintCodeLines(const CCodeLines& lines)
	{
		CCodeWriter writer;
		writer.WriteLines(lines);
		printf("%s", writer.m_code.c_str());
	}
}