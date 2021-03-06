/*!
@file TargetEscape.cpp
@brief TargetEscapeなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "EnState_LoseTarget.h"
#include "I_Escape.h"

#include "MyUtility.h"
#include "Velocity.h"
#include "EnemyRotationCtrl.h"
#include "EyeSearchRange.h"

#include "DebugObject.h"

namespace basecross {

	void TargetEscape::EyeSearch() {
		auto eye = GetGameObject()->GetComponent<EyeSearchRange>(false);
		if (eye) {
			if (eye->IsLookTarget(m_target.GetShard())) {
				CalucNextNode();
				m_outSightCount = 0;
			}
		}
	}

	void TargetEscape::Rotation() {
		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (velocity && rotation) {
			rotation->SetDirect(velocity->GetVelocity());
		}
	}

	void TargetEscape::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {  //Astarが無かったら
			return;
		}

		astar->UpdateVelocityMove(GetVelocityMaxSpeed(),GetArriveNearRange());
		//DebugObject::sm_wss << L"es";
		if(astar->IsRouteEnd()) {  //最終場所まで就いたら
			TargetRayCheck();
		}
	}

	void TargetEscape::TargetRayCheck() {
		//障害物が合ったら
		if (maru::MyUtility::IsRayObstacle(GetGameObject(),m_target.GetShard())) {
			m_outSightCount++;
		}
		else {  //無かったら
			m_outSightCount = 0;
		}

		ChangeStateCheck();
	}

	void TargetEscape::ChangeStateCheck() {
		if (m_outSightCount > m_alertReleaseNum) { //指定回数逃げ切ったら
			SuccessEscape(); //逃げ切り成功
		}
		else {
			//今のノードから一番遠いノードを選択する。
			CalucNextNode();
		}
	}

	void TargetEscape::CalucNextNode() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->SearchAstarEscapeNextRoute(m_target.GetShard());  //次に逃げるべきノードの検索
		}
	}

	void TargetEscape::SuccessEscape() {  //逃げ切り成功
		auto escape = GetGameObject()->GetComponent<I_Escape>(false);
		if (escape) {
			//DebugObject::sm_wss << endl << to_wstring(m_outSightCount) <<endl << L"escape";
			escape->SuccessEscape();
		}
	}

	void TargetEscape::OnCreate() {
		SetUpdateActive(false);
		SetArriveNearRange(1.0f);
		SetVelocityMaxSpeed(10.0f);
	}

	void TargetEscape::OnUpdate() {
		Move();  //ノードまで移動
		Rotation();

		//敵を発見したらもう一回探索
		EyeSearch();
	}

}

//endbasecross