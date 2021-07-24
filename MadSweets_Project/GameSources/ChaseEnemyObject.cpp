/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "ChaseEnemyObject.h"

#include "ChaseEnemy.h"
#include "AstarCtrl.h"

#include "TargetChase.h"
#include "PlowlingMove.h"
#include "EyeSearchRange.h"
#include "ReturnPlowlingPosition.h"
#include "EnemyRotationCtrl.h"
#include "Handy_Attack.h"

namespace basecross {

	void ChaseEnemyObject::CreatePlowlingRoute() {
		std::vector<Vec3> poss = {
			//{+0.0f ,+0.0f ,+0.0f},//0
			//{+5.0f ,+0.0f ,+0.0f},
			//{-5.0f ,+0.0f ,+0.0f},//2
			//{-1.0f ,+5.0f ,+0.0f},
			//{+0.0f ,-5.0f ,+0.0f},//4
			//{+5.0f ,+5.0f ,+0.0f},
			//{+10.0f ,+0.0f ,+0.0f},//6
			//{+6.0f ,+4.0f ,+0.0f},
			//{+2.0f ,+2.0f ,+0.0f}, //8

			{ +0.0f, +1.0f, +0.0f},//0
			{-12.0f, +1.0f,-12.0f},
			{+12.0f, +1.0f,-12.0f},//2
			{+11.0f, +1.0f,+11.0f},
			{ +0.0f, +1.0f,+12.0f},//4
			{-10.0f, +1.0f,+12.0f},
			{-12.0f, +1.0f, +7.0f},//6
			{-12.0f, +1.0f, -6.0f},
		};

		AddComponent<PlowlingMove>(poss);
	}

	void ChaseEnemyObject::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		draw->SetDiffuse(Col4(0.0f,0.0f,1.0f,1.0f));

		//AddComponent<AstarCtrl>();
		AddComponent<TargetChase>();
		AddComponent<EyeSearchRange>();
		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		CreatePlowlingRoute();

		AddComponent<Handy_Attack>();

		//本体は最後にする。
		AddComponent<ChaseEnemy>();

		auto col = AddComponent<CollisionObb>();
	}

}

//endbasecross