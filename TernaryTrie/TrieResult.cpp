#include "TrieResult.h"

void __cdecl CTrieResult::Clear()
{
	m_result.clear();
}

void __cdecl CTrieResult::Append(const ITrieResultItem* item)
{
	m_result.emplace_back(item);
}

const ITrieResultItem* __cdecl CTrieResult::getResultElement(const unsigned int idx)
{
	if (idx < m_result.size())
	{
		return (const ITrieResultItem*)(& m_result[idx]);
	}
	return nullptr;
}

const unsigned int __cdecl CTrieResult::getResultSize()
{
	return m_result.size();
}
