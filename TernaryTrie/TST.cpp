#include "TST.h"
#include <algorithm>
#include <queue>

void SpaceString(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
        [](char c) { return ' '; });
}

void TST::InsertTst(std::string& key)
{
    std::shared_ptr<Node> node = tree;
    std::shared_ptr<Node> prev = tree;

    unsigned int cidx = 0u;
    for (; node != nullptr && cidx < key.length();)
    {
        char& c = key[cidx];
        if (c < node->Char)
        {
            prev = node;
            node = node->lhs;
        }
        else if (c > node->Char)
        {
            prev = node;
            node = node->rhs;
        }
        else
        {
            prev = node;
            cidx++;
            node = node->mid;
        }
    }

    // string is alreayd in trie
    if (cidx == key.length()) return;

    node = std::make_shared<Node>();
    if (!tree)
    {
        tree = node;
    }
    else if (prev->Char < key[cidx])
    {
        prev->rhs = node;
    }
    else if (prev->Char > key[cidx])
    {
        prev->lhs = node;
    }
    else
    {
        prev->mid = node;
    }
    node->Char = key[cidx++];

    for (; cidx < key.length(); cidx++)
    {
        node->mid = std::make_shared<Node>();
        node->mid->Char = key[cidx];
        node = node->mid;
    }
    node->value = key;
};

void TST::RemoveTst(std::string& key)
{};

void TST::CollectItems(std::string& prefix, std::shared_ptr<Node>& node, std::vector<std::string>& resultContainer, ITrieQueryCancellation* cancellation)
{
    //if (cancellation && cancellation->isCancelled())
    //{
    //    return;
    //}

    if (node)
    {

        if (!node->value.empty())
        {
            resultContainer.push_back(node->value);
        }
        
        if (node->lhs)
        {
            std::string lhs = prefix;
            CollectItems(lhs, node->lhs, resultContainer, cancellation);
        }
        if (node->mid)
        {
            std::string key = prefix.append(&node->Char);
            CollectItems(key, node->mid, resultContainer, cancellation);
        }
        if (node->rhs)
        {
            std::string rhs = prefix;
            CollectItems(rhs, node->rhs, resultContainer, cancellation);
        }
        
    }
}

std::shared_ptr<TST::Node> TST::SearchTst(std::string& key)
{
    std::shared_ptr<Node> node = tree;
    unsigned int i = 0;
    for (; node && i < key.length(); )
    {
        if (key[i] < node->Char)
        {
            node = node->lhs;
        }
        else if (key[i] > node->Char)
        {
            node = node->rhs;
        }
        else
        {
            i++;
            if (i <= key.length())
            {
                node = node->mid;
            }

        }
    }

    if (i == key.length())
    {
        // root of subtree
        return node;
    }

    return std::make_shared<TST::Node>();
};


TST_TxtVisualiser::TST_TxtVisualiser(std::string fname, unsigned RowWidth)
{
    m_file.open(fname);
    m_linebuffer.resize(RowWidth, ' ');
}

void TST_TxtVisualiser::RenderTree(std::shared_ptr<TST::Node> tree)
{
    if (m_file)
    {
        std::queue<std::vector<TST::Node*>> _processQueue;
        _processQueue.push(std::vector{ tree.get() });
        size_t mid = m_linebuffer.size() / 2;
        size_t nodesize = 3;
        size_t row = 0;
        size_t nodeoffset = 0;
        while (!_processQueue.empty())
        {
            std::vector<TST::Node*> curr = _processQueue.front();
            _processQueue.pop();
            std::vector<TST::Node*> next;

            unsigned nodeCnt = 0u;
            unsigned c_index = mid - (nodeoffset / 2);
            nodeoffset = row > 0
                ? (row * 3) * nodesize
                : 1;
            for (auto n = curr.begin(); n != curr.end(); n++)
            {
                TST::Node* node = *n;

                m_linebuffer[c_index] = !node ? '.' : node->Char;
                next.push_back(!node ? node : node->lhs.get());
                next.push_back(!node ? node : node->mid.get());
                next.push_back(!node ? node : node->rhs.get());
                nodeCnt++;

                if (nodeCnt % 3 == 0)
                    c_index += nodesize;
                else
                    c_index++;
            }
            m_file << m_linebuffer << std::endl;
            SpaceString(m_linebuffer);

            row++;

            bool anyNodes = false;
            for (auto& n : next)
            {
                anyNodes |= n != nullptr;
            }

            if (anyNodes) _processQueue.push(next);
        }
    }
}