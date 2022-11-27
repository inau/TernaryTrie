#include "ITrieExports.h"
#include "Trie.h"
#include "TrieItem.h"
#include "TrieResult.h"

ITrie* TrieExports::CreateTrieObject()
{
    return new CTrie();
}

void TrieExports::DisposeTrie(ITrie* piTrie)
{
    if (piTrie)
    {
        delete piTrie;
        piTrie = nullptr;
    }
}

unsigned int TrieExports::Size(ITrie* piTrie)
{
    if (piTrie)
    {
        return piTrie->getSize();
    }
    return 0u;
}

void TrieExports::Add(ITrie* piTrie, const char* str)
{
    if (piTrie && str)
    {
        piTrie->Add(str);
    }
}

void TrieExports::Search(ITrie* piTrie, const char* str, ITrieResult* resultContainer, ITrieQueryCancellation* cancellation)
{
    if (piTrie && str)
    {
        piTrie->Search(str, resultContainer, cancellation);
    }
}

// ------------------------
ITrieResult* TrieExports::CreateResultObject()
{
    return new CTrieResult;
}

void TrieExports::DisposeResult(ITrieResult* piTrie)
{
    if (piTrie)
    {
        delete piTrie;
        piTrie = nullptr;
    }
}

const ITrieResultItem* TrieExports::getResultElement(ITrieResult* pi, const unsigned int idx)
{
    if (pi)
    {
        return pi->getResultElement(idx);
    }
    return nullptr;
}

const unsigned int TrieExports::getResultSize(ITrieResult* pi)
{
    if (pi)
    {
        return pi->getResultSize();
    }
    return 0u;
}

char* TrieExports::ItemGetText(ITrieResultItem* piTrie)
{
    if (piTrie)
    {
        return (char*)(piTrie->getText());
    }
    return nullptr;
}
