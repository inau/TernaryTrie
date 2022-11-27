#pragma once
#include <string>
#include "ITrie.h"
#include "TrieItem.h"
#include <vector>
#include <memory>

class CTrieResult : public ITrieResult
{
protected:
	std::vector<CTrieItem> m_result;

public:
	CTrieResult() {}

	// Inherited via ITrieResult
	void __cdecl Clear() override;
	void __cdecl Append(const ITrieResultItem* item) override;
	const ITrieResultItem* __cdecl getResultElement(const unsigned int idx) override;
	const unsigned int __cdecl getResultSize() override;

};

