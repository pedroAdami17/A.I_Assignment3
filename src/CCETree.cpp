#include "CCETree.h"

CCETree::CCETree()
{
	m_buildTree();
}

CCETree::~CCETree()
= default;

void CCETree::Update()
{
	m_CurrentHealthNode->setHasHealth(getAgent()->hasHealth());
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
	m_CurrentHealthNode = new CurrentHealthCondition();
	m_treeNodeList.push_back(m_CurrentHealthNode); //node 0

	m_LOSNode = new LOSCondition();
	AddNode(m_CurrentHealthNode, m_LOSNode, RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_LOSNode); //node 1

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode, LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode); //node 2

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode); //node 3

	TreeNode* HealthNode = AddNode(m_CurrentHealthNode, new FleeAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(HealthNode); // node 4

	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(patrolNode); //node 5

	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(moveToLOSNode); //node 6

	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(moveToPlayerNode); //node 7

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new CCEAttackAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(attackNode); //node 8
}
