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

		auto draw = AddComponent<BcPNTBoneModelDraw>();
		draw->SetMeshResource(L"Handy");
		draw->AddAnimation(L"Run",5,10,true,30.0f);
		
		auto col = AddComponent<CollisionObb>();
	}

	void MTestEnemyObject::OnUpdate() {
		AnimationCtrl();
	}
	
	void MTestEnemyObject::StartPlowlingTest() {
		//œpœjƒeƒXƒg
		std::vector<Vec3> poss = {
			{ +0.0f, +1.0f, +0.0f},//0
			{-12.0f, +1.0f,-12.0f},
			{+12.0f, +1.0f,-12.0f},//2
			{+11.0f, +1.0f,+11.0f},
			{ +0.0f, +1.0f,+12.0f},//4
			{-10.0f, +1.0f,+12.0f},
			{-12.0f, +1.0f, +7.0f},//6
			{-12.0f, +1.0f, -6.0f},
		};
		auto plow = AddComponent<PlowlingMove>();
		plow->SetPositions(poss);
	}

	void MTestEnemyObject::AnimationCtrl() {
		auto anime = GetComponent<BcPNTBoneModelDraw>();
		
		auto delta = App::GetApp()->GetElapsedTime();
		float speed = 1.0f;

		anime->UpdateAnimation(delta * speed);
	}

}

//endbasecross