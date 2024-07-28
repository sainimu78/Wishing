//namespace tq
//{
//	namespace TestLiteSharedPointer
//	{
//		static uint32 g_CA_instancesCount = 0;
//
//		class CA
//		{
//		public:
//			CA()
//				: m_str("nihao")
//			{
//				g_CA_instancesCount++;
//				printf("CA constructed, %u\n", g_CA_instancesCount);
//			}
//			virtual ~CA()
//			{
//				printf("CA destructed, %d\n", g_CA_instancesCount);
//				g_CA_instancesCount--;
//			}
//			void Print()
//			{
//				printf("%s\n", m_str.c_str());
//			}
//
//		private:
//			std::string m_str;
//		};
//
//		class CB : public CA
//		{
//		public:
//			CB()
//			{
//				printf("CB constructed, %u\n", g_CA_instancesCount);
//			}
//			virtual ~CB() override
//			{
//				printf("CB destructed, %d\n", g_CA_instancesCount);
//			}
//		};
//
//		template <typename TClass>
//		using TTestLiteSharedPointer = ClassMemory::TLiteSharedPointer<TClass, CDefaultMemory>;
//
//		static void TestLiteSharedPointer()
//		{
//			{
//				TTestLiteSharedPointer<CA> a;
//				{
//					ClassMemory::TLiteSharedPointer<CA, CDefaultMemory> b(ClassMemory::New<CB, CDefaultMemory>());
//					if (auto e = b)
//					{
//						e->Print();
//					}
//					if (auto e = a)
//					{
//						e->Print();
//					}
//					a = b;
//					if (auto e = a)
//					{
//						e->Print();
//					}
//					if (a != NULL)
//					{
//						a->Print();
//					}
//					if (NULL != a)
//					{
//						a->Print();
//					}
//
//					TTestLiteSharedPointer<CA> c;
//					TTestLiteSharedPointer<CB> d;
//					c = d;
//					d = c;
//				}
//				printf("");
//			}
//			printf("");
//		}
//	}
//}