/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "MTestEnemyObject.h"

#include "MTestEnemy.h"
#include "PlowlingMove.h"

namespace basecross {

	void MTestEnemyObject::OnCreate() {
		AddComponent<MTestEnemy>();

		auto draw = AddComponent<BcPNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		
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