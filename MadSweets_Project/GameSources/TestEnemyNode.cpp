/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "TestEnemyNode.h"

#include "DebugObject.h"

namespace basecross {

	void TestEnemyNode::OnStart() {
		DebugObject::AddString(L"TestEnemyNodeStart");
	}

	void TestEnemyNode::OnUpdate() {

	}

	void TestEnemyNode::OnExit() {

	}
}

//endbasecorss