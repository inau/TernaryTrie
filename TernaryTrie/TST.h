#pragma once
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include "ITrie.h"

class TST
{
public:
	class Node
	{
	public:
		char Char;
		std::shared_ptr<Node> lhs;
		std::shared_ptr<Node> mid;
		std::shared_ptr<Node> rhs;
		std::string value;
	};

protected:
	std::shared_ptr<Node> tree;

public:
	void InsertTst(std::string& key);
	void RemoveTst(std::string& key);
	std::shared_ptr<TST::Node> SearchTst(std::string& key);

	void CollectItems(std::string& prefix, std::shared_ptr<TST::Node>& node, std::vector<std::string>& resultContainer, ITrieQueryCancellation* cancellation);
};

class TST_TxtVisualiser
{
protected:
	std::ofstream m_file;
	std::string m_linebuffer;
public:
	TST_TxtVisualiser(std::string fname, unsigned RowWidth);
	void RenderTree(std::shared_ptr<TST::Node> tree);
};

