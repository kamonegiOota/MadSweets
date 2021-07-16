/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "MTestEnemyObject.h"
#include "MTestBox.h"

namespace basecross {

	void AstarCtrl::OnCreate() {
		auto target = GetStage()->AddGameObject<MTestEnemyObject>();
		target->GetComponent<Transform>()->SetPosition(Vec3(5.0f,+5.0f,0.0f));

		transform->SetPosition(Vec3(-5.0f, 0.0f, 0.0f));
		m_astar.SearchAstarStart(GetGameObject(),target);
	}

	void AstarCtrl::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto speed = 3.0f;

		auto nodePos = m_astar.CalucTargetNode(GetGameObject());
		auto toVec = nodePos - transform->GetPosition();

		auto pos = transform->GetPosition();
		pos += toVec.GetNormalized() * delta * speed;
		transform->SetPosition(pos);
	}
}

//endbasecross