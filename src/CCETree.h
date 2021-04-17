#pragma once
#ifndef __CCE_TREE__
#define __CCE_TREE__
#include "DecisionTree.h"

class CCETree final : public DecisionTree
{
public:
	CCETree();
	~CCETree();

	void Update();
	std::string MakeDecision();


private:
	void m_buildTree();

	LOSCondition* m_LOSNode;
	RadiusCondition* m_RadiusNode;
	CloseCombatCondition* m_CloseCombatNode;
	CurrentHealthCondition* m_CurrentHealthNode;

	std::vector<TreeNode*>m_treeNodeList;
};
#endif // defined (__CCE_TREE__)
