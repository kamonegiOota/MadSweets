/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "HandyObject.h"

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

#include"AnimationHelper.h"

#include "HandyAnimator.h"
#include "WallEvasion.h"

#include "TactileObject.h"

namespace basecross {

	void HandyObject::CreatePlowlingRoute() {
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

		AddComponent<PlowlingMove>(poss);
		transform->SetPosition(poss[0]);
	}

	void HandyObject::CreateTactle() {
		auto tactile = GetStage()->Instantiate<TactileObject>();
		tactile->SetParent(GetThis<GameObject>());

		AddComponent<WallEvasion>(tactile->GetComponent<WallEvasionTactile>(false));
	}

	void HandyObject::OnCreate() {
		//メッシュの調整用Mat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		auto draw = AddComponent<PNTBoneModelDraw>();
		draw->SetMeshResource(L"Handy_Walk");
		//draw->SetMeshResource(L"Cara_Walk");
		//draw->SetMeshResource(L"Ashi_Walk");
		//draw->AddAnimation(L"Run", 0, 60, true, 30.0f);
		draw->SetMeshToTransformMatrix(spanMat);

		AddComponent<HandyAnimatorCtrl>(draw);

		//AddComponent<AstarCtrl>();
		AddComponent<TargetChase>();
		AddComponent<TargetProbe>();
		AddComponent<EyeSearchRange>();
		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		AddComponent<Velocity>();
		AddComponent<ProbeAstarMove>();
		AddComponent<EnemyEar>();   //耳
		AddComponent<CheckTargetPos>();
		CreatePlowlingRoute();

		AddComponent<Handy_Attack>();
		AddComponent<ThrowCtrl>();

		//本体は最後にする。
		AddComponent<ChaseEnemy>();

		auto col = AddComponent<CollisionObb>();

		CreatePlowlingRoute();
		CreateTactle();
		//CreateAnimetor();
	}

	void HandyObject::OnUpdate() {
		//testアニメーション実装
		//auto anime = GetComponent<PNTBoneModelDraw>();
		//auto delta = App::GetApp()->GetElapsedTime();
		//float speed = 1.0f;

		//anime->UpdateAnimation(delta * speed);
	}

}

//endbasecross