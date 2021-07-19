/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "MTestEnemyObject.h"

#include "MTestEnemy.h"
#include "PlowlingMove.h"
#include "AstarCtrl.h"

namespace basecross {

	void MTestEnemyObject::OnCreate() {
		AddComponent<MTestEnemy>();
		AddTag(L"MTestEnemy");

		auto draw = AddComponent<BcPNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		
		auto col = AddComponent<CollisionObb>();
	}
	
	void MTestEnemyObject::StartPlowlingTest() {
		//徘徊テスト
		std::vector<Vec3> poss = {
			{0.0f,0.0f,+5.0f},
			{0.0f,0.0f,+0.0f},
			{0.0f,+2.0f,+0.0f},
			{0.0f,-2.0f,0.0f}
		};
		auto plow = AddComponent<PlowlingMove>();
		plow->SetPositions(poss);
	}

}

//endbasecross