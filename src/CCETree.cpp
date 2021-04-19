#include "CCETree.h"

CCETree::CCETree()
{
	m_buildTree();
}

CCETree::~CCETree()
= default;

void CCETree::Update()
{
	m_LOSNode->setLOS(getAgent()->hasLOS());
}

std::string CCETree::MakeDecision()
{
	Update();
	auto currentNode = m_treeNodeList[0];

	while (!currentNode->isLeaf)
	{
		currentNode = (currentNode->data) ? (currentNode->Right) : (currentNode->Left);
	}

	return currentNode->name;
}

void CCETree::m_buildTree()
{
	//add the root node
	m_LOSNode = new LOSCondition();
	m_treeNodeList.push_back(m_LOSNode); //node 0

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode, LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode); //node 1

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode); //node 2

	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(patrolNode); //node 3

	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(moveToLOSNode); //node 4

	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(moveToPlayerNode); //node 5

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new CCEAttackAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(attackNode); //node 6
}
