/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetProbe.h"
#include "AstarCtrl.h"
#include "SearchHidden.h"
#include "BaseEnemy.h"
#include "EnState_LoseTarget.h"
#include "EnState_Plowling.h"

#include "Velocity.h"
#include "UtilVelocity.h"
#include "MyUtility.h"
#include "EnemyRotationCtrl.h"

#include "FixedBox.h"
#include "PlayerObject.h"

namespace basecross {

	void TargetProbe::AddNode(const Vec3& position) {
		//return;
		vector<shared_ptr<GameObject>> obstacleObjs;
		vector<shared_ptr<GameObject>> excluteObjs;

		MyUtility::AddObjects<StageObject>(obstacleObjs); //障害物の対象をStageObjectにする
		excluteObjs.push_back(GetGameObject()); //自分を障害物から省く
		MyUtility::AddObjects<PlayerObject>(excluteObjs);
		MyUtility::AddComponents<BaseEnemy>(excluteObjs);

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		m_newNodeIndex = astar->AddNode(position, obstacleObjs, excluteObjs);
	}

	void TargetProbe::RemoveNode() {
		//return;
		if (m_checkHideObj == nullptr) {
			return;
		}

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		astar->RemoveNode(m_newNodeIndex);
	}

	void TargetProbe::SetAstarRondomHideObject() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			//近くのオブジェクトからランダムに捜索対象のオブジェクトを選択。
			auto hideObj = SearchHidden::SearchRandomHiddenObject(GetGameObject(), m_searchRange, m_checkHideObj);

			DebugObject::sm_wss << endl << L"RandomHide" <<  endl;

			if (hideObj == nullptr) {  //近くに隠れるオブジェクトが無かったら
				//ChangeState();
				return;
			}
			
			//ノードの追加と削除
			//RemoveNode();
			//AddNode(hideObj->GetComponent<Transform>()->GetPosition()); 

			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
			m_moveFunc = &TargetProbe::AstarMove;
		}
	}

	void TargetProbe::ChangeState() {
		m_probCount = 0;

		auto enemy = GetGameObject()->GetComponent<BaseEnemy>();
		if (enemy) {
			enemy->ChangeStateMachine<EnState_LoseTarget>();  //見失った状態にする。
		}
	}

	void TargetProbe::RouteEnd() {
		//本来はここでオブジェクトの中を覗く処理。
		m_probCount++;

		if (m_probCount >= m_numPorb) {  //指定回数調べたら。
			ChangeState();
		}
		else {  //まだカウントが過ぎていなかったら。
			SetAstarRondomHideObject();  //もう一度調べる。
		}
	}

	void TargetProbe::TargetMove() {
		auto veloComp = GetGameObject()->GetComponent<Velocity>();
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_checkHideObj);

		if (veloComp) {
			auto velocity = veloComp->GetVelocity();
			auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, toVec, GetVelocityMaxSpeed(), GetArriveNearRange());

			veloComp->SetForce(force);

			//向きの調整
			auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
			if (rotation) {
				rotation->SetDirect(veloComp->GetVelocity());
			}
		}

		//ターゲットの近くまで来たら
		constexpr float NearRange = 2.0f;
		if (toVec.length() <= NearRange) {
			RouteEnd();
		}
	}

	void TargetProbe::AstarMove() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetArriveNearRange());

			//対象の障害物判定がなくなったらでもいいかも？
			if (astar->IsRouteEnd()) {
				m_moveFunc = &TargetProbe::TargetMove;
				//RouteEnd();
			}
		}
	}

	void TargetProbe::ResetProbe() {
		m_probCount = 0;
		m_moveFunc = nullptr;
		m_checkHideObj = nullptr;
	}

	void TargetProbe::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetProbe::OnUpdate() {
		if (m_moveFunc) {
			m_moveFunc(*this);
		}
		else {
			ChangeState();
		}
	}

	void TargetProbe::StartProb() {
		ResetProbe();
		SetAstarRondomHideObject();
	}

	void TargetProbe::StartProb(const shared_ptr<GameObject>& target) {
		ResetProbe();
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->SearchAstarStart(target);
			m_checkHideObj = target;
			m_moveFunc = &TargetProbe::TargetMove;
		}
	}

}

//endbasecross