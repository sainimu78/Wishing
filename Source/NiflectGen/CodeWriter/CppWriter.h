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
		struct SIncludeDerectiveData
		{
			Niflect::CString m_incPath;
			bool m_isFromSystemHeaderSearchPaths;
		};
		static void Write(const Niflect::TArrayNif<SIncludeDerectiveData>& vecIncData, CCodeLines& lines)
		{
			WriteIncludeDirectives(vecIncData, lines);
		}
		static void WriteIncludeDirectives(const Niflect::TArrayNif<SIncludeDerectiveData>& vecIncData, CCodeLines& lines)
		{
			for (auto& it : vecIncData)
				lines.push_back(NiflectUtil::FormatString("#include \"%s\"", it.m_incPath.c_str()));
		}
		static Niflect::CString ConvertToIncludePath(const Niflect::CString& filePath, const Niflect::TArrayNif<Niflect::CString>& vecSearchPath)
		{
			Niflect::CString incPath;
			InternalConvertToIncludePath(filePath, vecSearchPath, incPath);
			return incPath;
		}
		static void ConvertFromHeaderFilePaths(const CCodeLines& vecFilePath, const CWritingHeaderSearchPaths& paths, CCodeLines& linesInclude)
		{
			Niflect::TArrayNif<SIncludeDerectiveData> vecIncData;
			CNoDupPathCollectorRef collectorRegular;
			CNoDupPathCollectorRef collectorBypass;
			for (auto& it : vecFilePath)
			{
				auto incPath = it;
				InternalConvertToIncludePath(it, paths.m_vecForRegularConversion, incPath);
				bool convertedOfRegular = collectorRegular.Cache(incPath);
				if (!convertedOfRegular)
				{
					InternalConvertToIncludePath(it, paths.m_vecForBypassConversion, incPath);
					collectorBypass.Cache(incPath);
				}
				if (convertedOfRegular)
				{
					vecIncData.push_back({incPath, false});
				}
			}

			Write(vecIncData, linesInclude);
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

	private:
		static bool InternalConvertToIncludePath(const Niflect::CString& filePath, const Niflect::TArrayNif<Niflect::CString>& vecSearchPath, Niflect::CString& incPath)
		{
			bool converted = false;
			for (auto& it : vecSearchPath)
			{
				ASSERT(!it.empty());
				auto pos = filePath.find(it);
				if (pos != std::string::npos)
				{
					auto prefixLength = pos + it.length();
					incPath = filePath.substr(prefixLength + 1, filePath.length() - prefixLength);
					converted = true;
					break;
				}
			}
			return converted;
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