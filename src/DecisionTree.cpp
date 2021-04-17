#include "DecisionTree.h"
#include <iostream>

DecisionTree::DecisionTree()
{
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::getAgent() const
{
	return m_agent;
}

void DecisionTree::setAgent(Agent* agent)
{
	m_agent = agent;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type)
{
	switch(type)
	{
	case LEFT_TREE_NODE:
		parent->Left = child_node;
		break;
	case RIGHT_TREE_NODE:
		parent->Right = child_node;
		break;
	}

	child_node->Parent = parent; //for backwards traversal (no recursion yet)
	return child_node;
}

void DecisionTree::DisplayTree()
{
	for (auto* node : m_treeNodeList)
		std::cout << node->name << std::endl;
}

