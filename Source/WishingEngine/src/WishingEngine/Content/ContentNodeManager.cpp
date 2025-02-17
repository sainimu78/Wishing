#include "WishingEngine/Content/ContentNodeManager.h"

namespace Wishing
{
	bool CContentNodeManager::Save(CRwNode* rw) const
	{
		AddRwUint32(rw, "FileNodesCount", m_vecFileNode.size());
		AddRwUint32(rw, "DirNodesCount", m_vecDirNode.size());
		return true;
	}
	//template <typename TArray, typename TElem>
	//static void ResizeObjectArray(TArray& vec)
	//{
	//	auto srcCnt = vec.size() - 1;
	//	auto diff = srcCnt - dstCnt;
	//	while ((diff--) > 0)
	//		vec.erase(vec.begin() + (vec.size() - 1));
	//	srcCnt = vec.size() - 1;
	//	diff = dstCnt - srcCnt;
	//	while ((diff--) > 0)
	//		vec.push->addItem("Default");
	//}
	template <typename TElem, typename TArray>
	static void ResizeObjectArrayTo(TArray& vec, uint32 cnt)
	{
		auto oldCnt = vec.size();
		vec.resize(cnt);
		auto newCnt = cnt - oldCnt;
		for (int32 idx = oldCnt; idx < cnt; ++idx)
			vec[idx] = Niflect::MakeShared<TElem>();
	}
	bool CContentNodeManager::Load(const CRwNode* rw)
	{
		ResizeObjectArrayTo<CContentFileNode2>(m_vecFileNode, FindRwUint32(rw, "FileNodesCount"));
		ResizeObjectArrayTo<CContentDirNode2>(m_vecDirNode, FindRwUint32(rw, "DirNodesCount"));
		return true;
	}
}