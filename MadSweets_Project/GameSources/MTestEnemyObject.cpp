/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
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
		//œpœjƒeƒXƒg
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