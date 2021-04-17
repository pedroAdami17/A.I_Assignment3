#include "RCETree.h"

RCETree::RCETree()
{
	m_buildTree();
}

RCETree::~RCETree()
= default;

void RCETree::Update()
{
	m_LOSNode->setLOS(getAgent()->hasLOS());
}

std::string RCETree::MakeDecision()
{
	Update();
	auto currentNode = m_treeNodeList[0];

	while (!currentNode->isLeaf)
	{
		currentNode = (currentNode->data) ? (currentNode->Right) : (currentNode->Left);
	}

	return currentNode->name;
}

void RCETree::m_buildTree()
{

}
