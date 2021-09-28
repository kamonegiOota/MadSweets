/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "CaraObject.h"

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
#include "ChaseAstarMove.h"
#include "PNTPointDraw.h"
#include "AstarPlowlingMove.h"
#include "EnemyEar.h"
#include "CheckTargetPos.h"
#include "TargetProbe.h"

#include"AnimationHelper.h"

#include "Cara_Attack.h"
#include "CaraAnimatorCtrl.h"
#include "WallEvasion.h"

#include "TactileObject.h"

#include "StatorBase.h"
#include "Trigger.h"
#include "BaseEnemy.h"
#include "EnemyMainStateMachine.h"
#include "CaraStator.h"

#include "ChaseEnemyStator.h"

// ���@�ǉ��� --------------------

#include "SoundHelper.h"
#include "HandySounder.h"

// ---------------------------------
namespace basecross {

	void CaraObject::CreatePlowlingRoute() {
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

	void CaraObject::CreateTactile() {
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
				AddComponent<WallEvasion>()->SetTactile(tactileComp);
			}
		}
	}

	void CaraObject::OnCreate() {
		//���b�V���̒����pMat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		auto draw = AddComponent<PNTBoneModelDraw>();
		draw->SetMeshResource(L"Cara_Walk");
		draw->SetMeshToTransformMatrix(spanMat);

		AddComponent<CaraAnimatorCtrl>(draw);

		//AddComponent<AstarCtrl>();
		AddComponent<TargetChase>();
		AddComponent<TargetProbe>();
		AddComponent<EyeSearchRange>();
		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		AddComponent<Velocity>();
		AddComponent<ChaseAstarMove>();
		AddComponent<EnemyEar>();   //��
		AddComponent<CheckTargetPos>();
		AddComponent<Cara_Attack>();

		//AddComponent<ChaseEnemyStator>();
		AddComponent<CaraStator>();

		//�{�͍̂Ō�ɂ���B
		AddComponent<ChaseEnemy>();

		auto col = AddComponent<CollisionObb>();

		CreatePlowlingRoute();
		CreateTactile();
	}

}