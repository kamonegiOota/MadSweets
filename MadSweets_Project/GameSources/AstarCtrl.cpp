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

	void AstarCtrl::Move() {
		if (m_astar.IsRouteEnd()) { //ƒ‹[ƒg‚ÌÅŒã‚Ü‚Å—ˆ‚½‚çˆ—‚ðŽ~‚ß‚éB
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		auto speed = 3.0f;

		auto nodePos = m_astar.CalucTargetNode(GetGameObject());
		auto toVec = nodePos - transform->GetPosition();

		auto pos = transform->GetPosition();
		pos += toVec.GetNormalized() * delta * speed;
		transform->SetPosition(pos);
	}

	void AstarCtrl::OnCreate() {
		//auto target = GetStage()->AddGameObject<MTestEnemyObject>();
		//target->GetComponent<Transform>()->SetPosition(Vec3(5.0f,+5.0f,0.0f));

		//transform->SetPosition(Vec3(-5.0f, 0.0f, 0.0f));
		//m_astar.SearchAstarStart(GetGameObject(),target);
	}

	void AstarCtrl::OnUpdate() {
		Move();
	}

	void AstarCtrl::SearchAstarStart(const std::shared_ptr<GameObject>& target) {
		m_astar.SearchAstarStart(GetGameObject(), target);
	}

	void AstarCtrl::SearchAstarStart(const Vec3& targetPos) {
		m_astar.SearchAstarStart(GetGameObject(), targetPos);
	}
}

//endbasecross