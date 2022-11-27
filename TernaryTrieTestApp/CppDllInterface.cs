using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace TernaryTrieTestApp
{
    internal class CppDLL
    {
        public static class Trie
        {
            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern IntPtr CreateTrieObject();
        
            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern void DisposeTrie(IntPtr pClassNameObject);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern uint Size(IntPtr pClassNameObject);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
            static public extern void Add(IntPtr pClassNameObject, string text);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
            static public extern void Search(IntPtr pClassNameObject, string text, IntPtr resultContainer, IntPtr cancellation);
        }

        public static class Result
        {
            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern IntPtr CreateResultObject();

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern void DisposeResult(IntPtr pClassNameObject);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern uint getResultSize(IntPtr pClassNameObject);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl)]
            static public extern IntPtr getResultElement(IntPtr pClassNameObject, uint index);

            [DllImport("TernaryTrie.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
            static public extern IntPtr ItemGetText(IntPtr pClassNameObject);
        }
    }
}
