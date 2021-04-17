#pragma once
#ifndef __RCE_TREE__
#define __RCE_TREE__
#include "DecisionTree.h"

class RCETree final : public DecisionTree
{
public:
	RCETree();
	~RCETree();

	void Update();
	std::string MakeDecision();


private:
	void m_buildTree();

	LOSCondition* m_LOSNode;
	RadiusCondition* m_RadiusNode;
	RangedCombatCondition* m_RangedCombatNode;

	std::vector<TreeNode*>m_treeNodeList;
};
#endif // defined (__RCE_TREE__)