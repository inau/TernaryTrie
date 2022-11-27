#pragma once
#include "ITrie.h"

#define TRIE_EXPORT extern __declspec(dllexport)

namespace TrieExports
{
	extern "C" 
	{
		// trie
		TRIE_EXPORT ITrie* CreateTrieObject();
		TRIE_EXPORT void DisposeTrie(ITrie* piTrie);

		TRIE_EXPORT unsigned int Size(ITrie* piTrie);
		TRIE_EXPORT void Add(ITrie* piTrie, const char* str);
		TRIE_EXPORT void Search(ITrie* piTrie, const char* str, ITrieResult* resultContainer, ITrieQueryCancellation* cancellation);

		// result
		TRIE_EXPORT ITrieResult* CreateResultObject();
		TRIE_EXPORT void DisposeResult(ITrieResult* piTrie);
		TRIE_EXPORT const ITrieResultItem* getResultElement(ITrieResult* pi, const unsigned int idx);
		TRIE_EXPORT const unsigned int getResultSize(ITrieResult* pi);

		// result item
		TRIE_EXPORT char* ItemGetText(ITrieResultItem* piTrie);
	}
}
