# Niflect

The C++ native-style type reflection.

## Example 1, The reflection code gen tool

### Step #1

An example header

```
#pragma once
#include "MyClass_gen.h"

NIF_T()
class CMyClass
{
	GENERATED_BODY()
public:
	CMyClass()
		: m_bool_1(false)
	{
	}
	void InitForTest()
	{
		m_std_string_0 = "My std string";
		m_bool_1 = true;
	}
	bool operator==(const CMyClass& rhs) const
	{
		return m_std_string_0 == rhs.m_std_string_0
			&& m_bool_1 == rhs.m_bool_1
			;
	}

private:
	NIF_F()
	std::string m_std_string_0;
	NIF_F()
	bool m_bool_1;
};
```

The macro tags like `NIF_T` are tags for reflection code gen.

### Step #2

Execute NiflectGenTool to generate reflection code, here is a batch script example, like

```
@..\ThirdParty\NiflectGenTool\bin\NiflectGenTool.exe ^
-n MyApp ^
-h ../MyClass.h ^
-a ../ThirdParty/Niflect/include/Niflect/CommonlyUsed/DefaultAccessorSetting.h ^
-I ../ThirdParty/Niflect/include ^
-I ../ ^
-p NiflectGenerated 
```

Then the reflection code will be generated

![1732206465218](Doc/Introduction/1732206465218.png)

#### About the DefaultAccessorSetting.h appears in the commandline args

This is one of the Niflect's feature, it's a header, called accessor setting header, for specifying type bindings in a way of C++ native style.

Here is a simplified version of the header

```
namespace DefaultAccessorSetting
{
	using namespace NiflectAccessorSetting;
	using namespace Niflect;

	NIF_AS_A() TSetting<CBoolAccessor, bool>;
	NIF_AS_A() TSetting<CSTLStringAccessor, std::string>;
}
```

This header can be interpreted by code completion tools.

Of course, users can implement settings like this to bind any `Accessor` for custom field serialization.

### Step #3

To save and load the example instance of `CMyClass ` with reflection info.

```
#include "MyClass.h"
#include "MyApp/ModuleReg/MyApp_private.h"
#include "Niflect/NiflectTable.h"
#include "Niflect/Serialization/JsonFormat.h"

int main()
{
	using namespace Niflect;

	CNiflectTable table;

	{
		Niflect::GeneratedInitialReg(&table);
		table.InitTypesLayout();
	}

	CRwNode rw;

	{
		CMyClass srcData;
		srcData.InitForTest();
		
		{
			// Save the 'srcData' instance to the 'rw' node
			auto type = StaticGetType<CMyClass>();
			type->SaveInstanceToRwNode(&srcData, &rw);
		}

		TSharedPtr<void*> dummy;
		{
			auto type = StaticGetType<CMyClass>();
			// Create CMyClass dummy instance from reflected type info.
			dummy = type->MakeSharedInstance<void*>();
			// Load the dummy instance from the 'rw' node
			type->LoadInstanceFromRwNode(dummy.Get(), &rw);
		}
		
		// Copy the loaded dummy instance to 'dstData'
		CMyClass dstData = *reinterpret_cast<CMyClass*>(dummy.Get());
		// Assert that the serialization and deserialization were successful
		ASSERT(srcData == dstData);
	}

	// Serialize 'rw' to JSON format and then print the result
	CStringStream ss;
	CJsonFormat::Write(&rw, ss);
	printf("%s\n", ss.str().c_str());

	return 0;
}
```

## Example 2, Being native

```
namespace MyScope
{
	static CMyFieldMeta MyGetNata()
	{
		return CMyFieldMeta().SetFriendlyName("Being native is all that matters");
	}

	class CMyClassNata : public Niflect::CNata
	{
		typedef CMyClassNata CThis;
	public:
		CThis& SetCategory(const Niflect::CString& name)
		{
			m_categoryName = name;
			return *this;
		}
		Niflect::CString m_categoryName;
	};

	NIF_T(CMyClassNata().SetCategory("My Default Category"))
	class CEngineObject
	{
		GENERATED_BODY()
	public:
		NIF_F(CMyFieldMeta()
			.SetFriendlyName("This is a nata in multi lines"))
		float m_float_0;
		NIF_F(MyGetNata())
		Niflect::CString m_string_2;
		NIF_F()
		std::string m_std_string_3;
		NIF_F()
		std::vector<float> m_std_array_float_4;
		NIF_F()
		std::vector<std::vector<float> > m_std_array_array_float_5;
		NIF_F()
		std::vector<bool> m_std_bits_6;
		NIF_F()
		std::map<std::string, std::vector<float> > m_std_map_string_array_float_7;
	};
}
```

This example demonstrates features as follows

### Feature #1, Nata

The Nata, such as `CMyClassNata`, refers to native-style type/field metadata. It can be interpreted by code completion tools, allowing users to efficiently write metadata code without the need to remember which properties are supported by the framework.

It's remarkable that users can wrap the Nata specification into other methods, such as `MyGetNata()`.

### Nested Templates & Specialized Templates

The nested templates, such as `std::vector<float>`, and the specialized templates, like `std::vector<bool>`, can be bound by specifying the settings in an accessor settings header, as shown below

```
using namespace NiflectAccessorSetting;

template <typename TInstance>
NIF_AS_A() TSetting<TSTLBitsArrayAccessor<TInstance>, std::vector<bool> >;

template <typename TInstance, typename T>
NIF_AS_A() TSetting<TSTLArrayAccessor<TInstance>, std::vector<T> >;

template <typename TInstance, typename T0, typename T1>
NIF_AS_A() TSetting<TSTLMapAccessor<TInstance>, std::map<T0, T1>, std::pair<T0, T1> >;
```

Again, the accessor setting headers allows users to bind their `Accessor` for their own custom serialization without needing to modify code of reflection code gen tool like NiflectGenTool.

More importantly, this type binding method is entirely in a native C++ style

## Summary

Being native is all that matters.

### Features

- C++ native-style type binding through accessor setting headers
  - Extremely easy to implement custom field serialization without modifying the code generation tool
- C++ native-style type/field metadata specification
  - Users can write metadata code in a native C++ style
- libclang-based parser, meaning that adapting to a coding standard is not required
  - Support for C++ type aliases using `typedef` or `using`

- Truly non-intrusive reflection implementation
  - No base type requirement for types being reflected.
  - Macro tags like `NIF_T` or `GENERATED_BODY` consist solely of `friend` declarations, without any definitions for fields or methods. (Macro tags can be easily renamed using `#define` as needed)
- Most extensible C++ native serialization method utilizing `RwTree`
  - Data is saved into the unified tree-like structure of `CRwNode`, allowing serialization into any other desired format.