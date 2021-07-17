/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "ChaseEnemyObject.h"

#include "ChaseEnemy.h"
#include "AstarCtrl.h"

#include "TargetChase.h"
#include "PlowlingMove.h"
#include "EyeSearchRange.h"

namespace basecross {

	void ChaseEnemyObject::CreatePlowlingRoute() {
		std::vector<Vec3> poss = {
			{0.0f,0.0f,+5.0f},
			{0.0f,0.0f,+0.0f},
			{0.0f,+2.0f,+0.0f},
			{0.0f,-2.0f,0.0f}
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
		CreatePlowlingRoute();

		AddComponent<ChaseEnemy>();
	}

}

//endbasecross