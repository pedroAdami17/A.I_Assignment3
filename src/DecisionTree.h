#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__
#include "Agent.h"
#include "TreeNode.h"
#include "TreeNodeType.h"
#include <string>
#include "LOSCondition.h"
#include "RadiusCondition.h"
#include "CloseCombatCondition.h"
#include "RangedCombatCondition.h"
#include "CurrentHealthCondition.h"
#include "PatrolAction.h"
#include "CCEAttackAction.h"
#include "RCEAttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "Flee.h"

class DecisionTree
{
public:
	//constructor and destructor
	DecisionTree();
	~DecisionTree();

	// Getters and setters 
	Agent* getAgent() const;
	void setAgent(Agent* agent);

	// for convenience
	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type);
	void DisplayTree(); //for debug

private:
	Agent* m_agent;

	std::vector<TreeNode*>m_treeNodeList;
};

#endif /* defined (__DECISION_TREE__) */


