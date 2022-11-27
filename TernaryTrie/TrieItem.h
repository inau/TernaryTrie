#pragma once
#include <string>
#include "ITrie.h"

class CTrieItem : public ITrieResultItem
{
protected:
	std::string m_text;

public:
	CTrieItem() {}
	CTrieItem(const ITrieResultItem* other)
		: m_text(other ? other->getText() : "") {}

	CTrieItem(const char* str)
		: m_text(str) {}

	// Inherited via ITrieResultItem
	const char* getText() const override;
};

