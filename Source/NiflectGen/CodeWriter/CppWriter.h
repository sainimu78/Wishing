#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/CodeWriter/CodeWriter.h"
#include "NiflectGen/CodeWriter/CodeRequirement.h"

namespace NiflectGen
{
	class CCppWriterRef
	{
	public:
		CCppWriterRef(Niflect::CString& code)
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
	class CCppWriter : public CCppWriterRef
	{
		typedef CCppWriterRef inherited;
	public:
		CCppWriter()
			: inherited(m_stm)
		{
		}

	private:
		Niflect::CString m_stm;
	};

	class CHeaderFilePathData
	{
	public:
		CHeaderFilePathData()
			: m_isPreservedHeadersOrder(false)
		{
			ASSERT(false);
		}
		CHeaderFilePathData(const Niflect::CString& path)
			: m_path(path)
			, m_isPreservedHeadersOrder(false)
		{
		}
		CHeaderFilePathData(const char* pszPath)
			: m_path(pszPath)
			, m_isPreservedHeadersOrder(false)
		{
		}
		CHeaderFilePathData(const Niflect::CString& path, bool isPreservedHeadersOrder)
			: m_path(path)
			, m_isPreservedHeadersOrder(isPreservedHeadersOrder)
		{
		}
		const Niflect::CString m_path;
		const bool m_isPreservedHeadersOrder;
	};
	using CHeaderFilePathDataArray = Niflect::TArrayNif<CHeaderFilePathData>;

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
			{
				char cL = '\"';
				char cR = '\"';
				if (it.m_isFromSystemHeaderSearchPaths)
				{
					cL = '<';
					cR = '>';
				}
				lines.push_back(NiflectUtil::FormatString("#include %c%s%c", cL, it.m_incPath.c_str(), cR));
			}
		}
		static Niflect::CString ConvertToIncludePath(const Niflect::CString& filePath, const Niflect::TArrayNif<Niflect::CString>& vecSearchPath)
		{
			Niflect::CString incPath;
			InternalConvertToIncludePath(filePath, vecSearchPath, incPath);
			return incPath;
		}
		static void ConvertFromHeaderFilePaths(const CHeaderFilePathDataArray& vecHeaderData, const CWritingHeaderSearchPaths& paths, CCodeLines& linesInclude)
		{
			Niflect::TArrayNif<Niflect::CString> vecIncPathPreservedOrder;
			Niflect::TArrayNif<Niflect::CString> vecIncPathSystem;
			Niflect::TArrayNif<Niflect::CString> vecIncPathUser;
			CNoDupPathCollectorRef collector;
			for (auto& it : vecHeaderData)
			{
				auto& path = it.m_path;
				auto incPath = path;
				bool isBypassFilePath = InternalConvertToIncludePath(path, paths.m_vecForBypassConversion, incPath);
				if (!isBypassFilePath)
					InternalConvertToIncludePath(path, paths.m_vecForRegularConversion, incPath);
				if (collector.Cache(incPath))
				{
					auto p = &vecIncPathUser;
					if (isBypassFilePath)
						p = &vecIncPathSystem;
					else if (it.m_isPreservedHeadersOrder)
						p = &vecIncPathPreservedOrder;
					p->push_back(incPath);
				}
			}
			Niflect::TArrayNif<SIncludeDerectiveData> vecIncData;
			for (auto& it : vecIncPathPreservedOrder)
				vecIncData.push_back({ it, false });
			for (auto& it : vecIncPathSystem)
				vecIncData.push_back({ it, true });
			for (auto& it : vecIncPathUser)
				vecIncData.push_back({ it, false });
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
			bool converted = false;//false 表示未经过转换, filePath 可能为正确的相对路径
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
			ASSERT(!filePath.empty());
			this->AddLine(NiflectUtil::FormatString("#include \"%s\"", filePath.c_str()));
		}
		void AddSystemInclude(const Niflect::CString& filePath)
		{
			ASSERT(!filePath.empty());
			this->AddLine(NiflectUtil::FormatString("#include <%s>", filePath.c_str()));
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

	static Niflect::CString ConvertToInternalFilePath(const Niflect::CString& relativeTypeRegFilePathNoExt)
	{
		auto fileNameNoExt = NiflectUtil::GetFileName(relativeTypeRegFilePathNoExt);
		auto internalFileNameNoExt = "_" + fileNameNoExt;
		Niflect::CString dirPath;
		NiflectUtil::GetParentDirPathSafe(relativeTypeRegFilePathNoExt, dirPath);
		auto internalRelativeTypeRegFilePathNoExt = internalFileNameNoExt;
		if (!dirPath.empty())
			internalRelativeTypeRegFilePathNoExt = NiflectUtil::ConcatPath(dirPath, internalFileNameNoExt);
		return internalRelativeTypeRegFilePathNoExt;
	}
}