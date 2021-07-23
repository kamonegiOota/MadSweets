/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "EscapeEnemyObject.h"

#include "EscapeEnemy.h"
#include "EyeSearchRange.h"
#include "PlowlingMove.h"
#include "TargetEscape.h"
#include "EnemyRotationCtrl.h"
#include "ReturnPlowlingPosition.h"

namespace basecross {

	void EscapeEnemyObject::CreatePlowlingRoute() {
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
	}

	void EscapeEnemyObject::OnCreate() {

		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		AddComponent<ReturnPlowlingPosition>();
		AddComponent<EnemyRotationCtrl>();
		AddComponent<EyeSearchRange>();
		AddComponent<TargetEscape>();
		CreatePlowlingRoute();

		AddComponent<EscapeEnemy>();

		auto col = AddComponent<CollisionObb>();
	}

}

//endbasecross