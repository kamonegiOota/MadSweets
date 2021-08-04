/*!
@file GraphNode.cpp
@brief GraphNodeÇ»Ç«é¿ëÃ
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
#include "ThrowCtrl.h"
#include "Velocity.h"
#include "ProbeAstarMove.h"
#include "PNTPointDraw.h"
#include "AstarPlowlingMove.h"
#include "EnemyEar.h"
#include "CheckTargetPos.h"
#include "TargetProbe.h"

namespace basecross {

	void ChaseEnemyObject::CreatePlowlingRoute() {

		//PlowlingParam param;
		//param.startPos = Vec3(0.0f, 1.0f, 0.0f);

		//AddComponent<AstarPlowlingMove>();

		//return;

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
		//auto draw = AddComponent<PNTStaticDraw>();
		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		draw->SetDiffuse(Col4(0.0f,0.0f,1.0f,1.0f));

		//AddComponent<AstarCtrl>();
		AddComponent<TargetChase>();
		AddComponent<EyeSearchRange>();
		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		AddComponent<Velocity>();
		AddComponent<ProbeAstarMove>();
		AddComponent<EnemyEar>();   //é®
		AddComponent<CheckTargetPos>();
		CreatePlowlingRoute();

		AddComponent<Handy_Attack>();
		AddComponent<ThrowCtrl>();
		AddComponent<TargetProbe>();

		//ñ{ëÃÇÕç≈å„Ç…Ç∑ÇÈÅB
		AddComponent<ChaseEnemy>();

		auto col = AddComponent<CollisionObb>();
	}

}

//endbasecross