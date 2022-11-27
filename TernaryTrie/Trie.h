#pragma once
#include <map>
#include "ITrie.h"
#include "TrieItem.h"
#include <vector>
#include <memory>
#include <fstream>
#include "TST.h"



class TrieDebugger
{
protected:
	std::ofstream m_file;
public:
	TrieDebugger(std::string fname);
	void Log(std::string msg);
};

class CTrie : public ITrie
{
protected:
	TST m_trie;
	std::map<std::string, CTrieItem> m_backingData;
	const bool ignoreCase;
	std::shared_ptr<TrieDebugger> _dbg;
	void Log(const std::string str);
public:
	CTrie(bool fignoreCase = true)
		: ignoreCase(fignoreCase) 
	{
#ifdef _DEBUG
		_dbg = std::make_shared<TrieDebugger>("trie_lib_debug.txt");
#endif // _DEBUG

	}

	// Inherited via ITrie
	void __cdecl Add(const char* str) override;
	void __cdecl Remove(const char* str) override;
	void __cdecl Search(const char* str, ITrieResult* resultContainer, ITrieQueryCancellation* cancellation) override;
	const unsigned int __cdecl getSize() override;
};