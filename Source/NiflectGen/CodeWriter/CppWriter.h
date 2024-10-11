#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/CodeWriter/CodeWriter.h"
#include "NiflectGen/CodeWriter/CodeRequirement.h"

namespace NiflectGen
{
	class CCppWriter
	{
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
		Niflect::CString m_code;
	};

	class CIncludesHelper
	{
	public:
		static void Write(const CNoDupPathCollector& pathCollector, CCodeLines& lines)
		{
			WriteIncludeDirectives(pathCollector.m_vecPath, lines);
		}
		static void WriteIncludeDirectives(const CCodeLines& vecIncludePath, CCodeLines& lines)
		{
			for (auto& it : vecIncludePath)
				lines.push_back(NiflectUtil::FormatString("#include \"%s\"", it.c_str()));
		}
		static Niflect::CString ConvertToIncludePath(const Niflect::CString& filePathAbs, const Niflect::TArrayNif<Niflect::CString>& vecSearchPath)
		{
			for (auto& it : vecSearchPath)
			{
				ASSERT(!it.empty());
				auto pos = filePathAbs.find(it);
				if (pos != std::string::npos)
				{
					auto prefixLength = pos + it.length();
					auto incPath = filePathAbs.substr(prefixLength + 1, filePathAbs.length() - prefixLength);
					return incPath;
				}
			}
			return filePathAbs;
		}
		static void WriteUsingNamespaces(const CNoDupPathCollector& pathCollector, CCodeLines& lines)
		{
			WriteUsingNamespaceDirectives(pathCollector.m_vecPath, lines);
		}
		static void WriteUsingNamespaceDirectives(const CCodeLines& vecIncludePath, CCodeLines& lines)
		{
			for (auto& it : vecIncludePath)
				lines.push_back(NiflectUtil::FormatString("using namespace %s;", it.c_str()));
		}
	};

	class CSimpleCppWriter
	{
	public:
		CSimpleCppWriter(Niflect::CString& data)
			: m_data(data)
		{
		}
		void AddHeaderFirstLine()
		{
			this->AddLine("#pragma once");
		}
		void AddInclude(const Niflect::CString& filePath)
		{
			this->AddLine(NiflectUtil::FormatString("#include \"%s\"", filePath.c_str()));
		}

	private:
		void AddLine(const Niflect::CString& text)
		{
			m_data += text;
			m_data += "\r\n";
		}

	private:
		Niflect::CString& m_data;
	};

	static void DebugPrintCodeLines(const CCodeLines& lines)
	{
		CCppWriter writer;
		writer.WriteLines(lines);
		printf("%s", writer.m_code.c_str());
	}
}