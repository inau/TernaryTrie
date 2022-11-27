#include "Trie.h"
#include <algorithm>
#include <queue>
void LowerCaseString(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
        [](char c) { return std::tolower(c); });
}

void __cdecl CTrie::Add(const char* str)
{
    std::string key(str);
    if (ignoreCase) { LowerCaseString(key); }

    if (m_backingData.count(key) == 0)
    {
        Log(key);

        CTrieItem item(str);
        m_backingData.emplace(key, item);
        m_trie.InsertTst(key);
    }
}

void __cdecl CTrie::Remove(const char* str)
{
    std::string key(str);
    if (ignoreCase) { LowerCaseString(key); }

    if (m_backingData.count(key) > 0)
    {
        m_backingData.erase(key);
        m_trie.RemoveTst(key);
    }
}

void __cdecl CTrie::Search(const char* str, ITrieResult* resultContainer, ITrieQueryCancellation* cancellation)
{
    std::string debug = "searching for";
    Log(debug);

    std::string key(str);
    if (ignoreCase) { LowerCaseString(key); }

    Log(key);

    if (resultContainer)
    {

        resultContainer->Clear();
        debug = "container cleared";
        Log(debug);
        std::shared_ptr<TST::Node> node = m_trie.SearchTst(key);
        
        std::vector<std::string> subtree;
        m_trie.CollectItems(key, node, subtree, cancellation);
        
        debug = "trie collected # items " + std::to_string(subtree.size());
        Log(debug);
        for(const std::string& item : subtree)
        {
         //   if (cancellation && cancellation->isCancelled()) return;

            if (m_backingData.count(item) > 0)
            {
                debug = "key found - " + item;
                Log(debug);
                resultContainer->Append(&m_backingData[item]);
            }
        }

    }
}

const unsigned int __cdecl CTrie::getSize()
{
    return m_backingData.size();
}
void CTrie::Log(const std::string str)
{
    if (_dbg)
    {
        _dbg->Log(str);
    }
}
;

TrieDebugger::TrieDebugger(std::string fname)
{
    m_file.open(fname);
}

void TrieDebugger::Log(std::string msg)
{
    if (m_file)
    {
        m_file << msg << std::endl;
    }
}
