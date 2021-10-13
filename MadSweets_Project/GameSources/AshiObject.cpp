/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "AshiObject.h"

#include "EscapeEnemy.h"
#include "AstarCtrl.h"

#include "TargetEscape.h"
#include "PlowlingMove.h"
#include "EyeSearchRange.h"
#include "ReturnPlowlingPosition.h"
#include "EnemyRotationCtrl.h"
#include "Handy_Attack.h"
#include "ThrowCtrl.h"
#include "Velocity.h"
#include "ChaseAstarMove.h"
#include "PNTPointDraw.h"
#include "AstarPlowlingMove.h"
#include "EnemyEar.h"
#include "CheckTargetPos.h"
#include "TargetProbe.h"

#include"AnimationHelper.h"

#include "AshiAnimatorCtrl.h"
#include "WallEvasion.h"

#include "TactileObject.h"


// 板橋　追加分 --------------------

#include "SoundHelper.h"
#include "HandySounder.h"

// ---------------------------------
namespace basecross {


	void AshiObject::CreatePlowlingRoute() {
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

	void AshiObject::CreateTactile() {
		struct Pair {
			Vec3 offset;
			Vec3 rotation;

			Pair(const Vec3& offset, const Vec3& rotation) :
				offset(offset), rotation(rotation)
			{}
		};

		auto pos = transform->GetPosition();
		Pair pairs[] = {
			{Pair(Vec3(+0.75f, 0.15f, 0.5f), Vec3(0.0f, +XM_PIDIV4, 0.0f))},
			{Pair(Vec3(-0.75f, 0.15f, 0.5f), Vec3(0.0f, -XM_PIDIV4, 0.0f))},
		};

		for (const auto& pair : pairs) {
			auto tactile = GetStage()->Instantiate<TactileObject>();
			auto trans = tactile->GetComponent<Transform>();
			trans->SetPosition(pos + pair.offset);
			trans->SetRotation(pair.rotation);
			tactile->SetParent(GetThis<GameObject>());

			auto tactileComp = tactile->GetComponent<TactileCtrl>(false);
			if (tactileComp) {
				auto evasion = AddComponent<WallEvasion>();
				evasion->SetTactile(tactileComp);
				evasion->SetMaxSpeed(20.0f);
			}
		}
	}

	void AshiObject::OnCreate() {
		//メッシュの調整用Mat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		auto draw = AddComponent<PNTBoneModelDraw>();
		draw->SetMeshResource(L"Ashi_Walk");
		draw->SetMeshToTransformMatrix(spanMat);

		AddComponent<AshiAnimatorCtrl>(draw);

		AddComponent<TargetEscape>();
		AddComponent<EyeSearchRange>();
		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		AddComponent<Velocity>();
		AddComponent<ChaseAstarMove>();
		AddComponent<EnemyEar>();   //耳
		AddComponent<CheckTargetPos>();

		AddComponent<EscapeEnemy>();

		auto col = AddComponent<CollisionObb>();

		CreatePlowlingRoute();
		CreateTactile();
	}

}

//endbasecross