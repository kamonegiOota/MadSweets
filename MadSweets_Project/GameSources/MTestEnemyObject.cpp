/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "MTestEnemyObject.h"

#include "MTestEnemy.h"

namespace basecross {

	void MTestEnemyObject::OnCreate() {
		AddComponent<MTestEnemy>();

		auto draw = AddComponent<BcPNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

	}

}

//endbasecross