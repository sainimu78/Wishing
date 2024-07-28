#pragma once
#include "Niflect/NiflectCommon.h"
#include <string>//for rapidjson macro RAPIDJSON_HAS_STDSTRING, eg: std::vector<std::basic_string<Ch> > keys() const
#include <vector>//for rapidjson macro RAPIDJSON_HAS_STDSTRING, eg: std::vector<std::basic_string<Ch> > keys() const
#include "Niflect/Serialization/Format/Json/rapidjson/document.h"
#include "Niflect/Serialization/Format/Json/rapidjson/stringbuffer.h"
#include "Niflect/Serialization/Format/Json/rapidjson/filewritestream.h"
//todo: writer可定义平台优化, 可将宏加到cmake中, RAPIDJSON_SSE2, RAPIDJSON_NEON
#include "Niflect/Serialization/Format/Json/rapidjson/writer.h"
#include "Niflect/Serialization/Format/Json/rapidjson/prettywriter.h"

namespace Niflect
{
	//todo: 计划实现线程堆内存allocator缓存, 用于runtime解析json
	template <typename TMemory>
	class CJson
	{
	private:
		class MyRapidjsonCrtAllocator {
		//该类从rapidjson/allocators.h中的CrtAllocator复制代码后修改而得
		public:
			MyRapidjsonCrtAllocator(size_t reserved = 0)
			{
			}
			static const bool kNeedFree = true;
			void* Malloc(size_t size) { 
				if (size) //  behavior of malloc(0) is implementation defined.
					return TMemory::Alloc(size);
				else
					return NULL; // standardize to returning NULL.
			}
			void* Realloc(void* originalPtr, size_t originalSize, size_t newSize) {
				(void)originalSize;
				if (newSize == 0) {
					TMemory::Free(originalPtr);
					return NULL;
				}
				return TMemory::Realloc(originalPtr, newSize);
			}
			static void Free(void *ptr)
			{
				TMemory::Free(ptr);
			}
		};

	public:
		typedef MyRapidjsonCrtAllocator AllocatorStack;//会释放内存
		typedef rapidjson::MemoryPoolAllocator<MyRapidjsonCrtAllocator> AllocatorPool;//不释放内存
		typedef AllocatorStack Allocator;
		typedef rapidjson::SizeType SizeType;
		//typedef rapidjson::CDocumentOption COption;
		typedef rapidjson::GenericValue<rapidjson::UTF8<>, Allocator> Object;
		typedef rapidjson::GenericDocument<rapidjson::UTF8<>, Allocator, Allocator> Document;
		typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<>, Allocator> StringBuffer;
		typedef rapidjson::Writer<rapidjson::UTF8<>, rapidjson::UTF8<>, Allocator> Writer;
		typedef rapidjson::PrettyWriter<StringBuffer, rapidjson::UTF8<>, rapidjson::UTF8<>, Allocator> PrettyWriter;

	public:
		template <typename T>
		static Object& ReadFromBuffer(Document& jd, const T psz)
		{
			//const auto parseOption = rapidjson::kParseStopWhenDoneFlag | rapidjson::kParseTrailingCommasFlag;
			jd.Parse(reinterpret_cast<const char*>(psz));
			if (jd.HasParseError())
			{
				auto error = jd.GetParseError();
				if(error != rapidjson::kParseErrorDocumentEmpty)
					LogError("Failed to parse json, error code: %d", error);//如果手工编辑过, 一般是语法错误, 如多或少逗号, 请检查"]", "}"附近的逗号或某处行末是否正确
			}
			return jd;
		}
		static Object& AsRoot(Document& jd)
		{
			if (jd.IsNull())
				jd.SetObject();
			return jd;
		}
		static void WriteToBuffer(const Object& joPar, StringBuffer& buffer)
		{
			PrettyWriter writer(buffer, &buffer.stack_.GetAllocator());
			joPar.Accept(writer);
		}
		static void WriteToBufferCompact(const Object& joPar, StringBuffer& buffer)
		{
			Writer writer(buffer, &buffer.stack_.GetAllocator());
			joPar.Accept(writer);
		}
	};
}

////begin, 读(已废弃的示例)
//auto ms = GetArchiveMananger()->Open("shaderex/shader_editor/test.sea");
//S3Util::Json::Document jd;
//S3Util::Json::Object joPar = S3Util::Json::ReadFromBuffer(jd, ms->GetPtr());
//S3Util::Json::Object::Array jaConn = joPar["Connections"].toArray();
//for (auto& it : jaConn)
//{
//	auto joConn = it.toObject();
//	printf("nodeFrom: %s\n", joConn["nodeFrom"].toString().c_str());
//	printf("nodeTo: %s\n", joConn["nodeTo"].toString().c_str());
//	printf("portIdxFrom: %d\n", joConn["portIdxFrom"].toInt());
//	printf("portIdxTo: %d\n", joConn["portIdxTo"].toInt());
//}
//S3Util::Json::StringBuffer buffer;
//S3Util::Json::WriteToBuffer(jd, buffer);
//std::cout << buffer.GetString() << std::endl;
////end

//begin, 写, 读
//{
//	using namespace Niflect;
//	using Json = CJson<CMemory>;
//		
//	size_t poolCapa = 0;//建议值 65536
//	size_t stackCapa = 0;//建议值 1024
//	Json::AllocatorStack stack;
//	//Json::AllocatorPool allocator(poolCapa, &stack);
//	Json::AllocatorStack allocator;
//
//	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//	Json::Document jd(&allocator, poolCapa, &stack);
//	auto& joPar = Json::ReadFromBuffer(jd, json);
//
//	{
//		joPar.AddMember("zeta", false, jd.GetAllocator());
//		joPar.AddMember("gama", "test string", jd.GetAllocator());
//		joPar.AddMember("delta", 123, jd.GetAllocator());
//
//		Json::Object v(rapidjson::kObjectType);
//		v.AddMember("nihao", 999, jd.GetAllocator());
//		Json::Object arr(rapidjson::kArrayType);
//		arr.PushBack(345, jd.GetAllocator());
//		arr.PushBack(6789, jd.GetAllocator());
//		v.AddMember("arr", arr, jd.GetAllocator());
//		joPar.AddMember("alpha", v, jd.GetAllocator());
//
//		const auto& refPar = joPar;
//		auto itFound = refPar.FindMember("stars");
//		if (itFound != refPar.MemberEnd())
//			printf("starts found\n");
//		else
//			printf("starts not found\n");
//
//		// 2. Modify it by DOM.
//		auto s = joPar.FindMember("stars");
//		if (s != joPar.MemberEnd())
//		{
//			s->value.SetInt(s->value.GetInt() + 1);
//		}
//
//		s = joPar.FindMember("project");
//		if (s != joPar.MemberEnd())
//		{
//			s->value.SetString((std::string(s->value.GetString()) + " is a shit").c_str(), jd.GetAllocator());
//		}
//	}
//		
//	{
//		Json::StringBuffer buffer(&allocator, poolCapa);
//		Json::WriteToBuffer(joPar, buffer);
//	
//		printf("%s\n", buffer.GetString());
//	}
//
//	{
//		auto itFound = joPar.FindMember("stars");
//		if (itFound != joPar.MemberEnd())
//			joPar.EraseMember(itFound);
//
//		Json::StringBuffer buffer(&allocator, poolCapa);
//		Json::WriteToBuffer(joPar, buffer);
//	
//		printf("%s\n", buffer.GetString());
//	}
//}
//end