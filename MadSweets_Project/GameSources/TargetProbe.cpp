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
#include "HandyAnimator.h"
#include "EnState_ProbeTarget.h"
#include "HiddenComponent.h"
#include "EnState_Attack.h"

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
				return;
			}
			
			//ノードの追加と削除
			RemoveNode();
			AddNode(hideObj->GetComponent<Transform>()->GetPosition()); 

			astar->SearchAstarStart(hideObj);
			m_checkHideObj = hideObj;
			m_moveFunc = &TargetProbe::AstarMove;
		}
	}

	void TargetProbe::InvestigateHideObj() {
		//アニメーションの再生s
		auto animeCtrl = GetGameObject()->GetComponent<HandyAnimatorCtrl>(false);
		if (animeCtrl) {
			auto animator = animeCtrl->GetAnimator();
			animator->GetMemberRefarence().hideSearchTrigger.Fire();
		}

		//敵が発見できるかどうか?
		//hideObjectのコライダーをoffにすることで判断
		SetHideObjCollisionUpdate(false);

		return;
		//現在は仮で判断している。
		auto hideComp = m_checkHideObj->GetComponent<HiddenComponent>(false);
		if (hideComp) {
			auto pos = hideComp->GetHideData().hideWorldPosition;
			auto toVec = m_target->GetComponent<Transform>()->GetPosition() - pos;
			if (toVec.length() <= 0.01f) {
				//ChangeState<EnState_Attack>(m_target);
			}
		}
	}

	void TargetProbe::RouteEnd() {
		//本来はここでオブジェクトの中を覗く処理。
		InvestigateHideObj();
		
		m_moveFunc = &TargetProbe::WaitInvestigateAnimationUpdateEnd;

		//速度を0にする。
		auto velocityComp = GetGameObject()->GetComponent<Velocity>(false);
		if (velocityComp) {
			velocityComp->Reset();
		}
	}

	void TargetProbe::WaitInvestigateAnimationUpdateEnd() {

	}

	void TargetProbe::TargetMove() {
		auto veloComp = GetGameObject()->GetComponent<Velocity>(false);
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
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
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

	void TargetProbe::SetHideObjCollisionUpdate(const bool isUpdate) {
		if (m_checkHideObj == nullptr) {
			return;
		}

		auto col = m_checkHideObj->GetComponent<Collision>(false);
		if (col) {
			if (col->GetUpdateActive() != isUpdate) {
				col->SetUpdateActive(isUpdate);
			}
		}
	}

	void TargetProbe::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetProbe::OnUpdate() {
		//m_moveFunc = nullptr;

		if (m_moveFunc) {
			m_moveFunc(*this);
		}
		else {
			SetHideObjCollisionUpdate(true);
			ChangeState<EnState_LoseTarget>();
		}
	}

	void TargetProbe::StartProb() {
		ResetProbe();
		SetAstarRondomHideObject();
	}

	void TargetProbe::StartProb(const shared_ptr<GameObject>& target) {
		ResetProbe();
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarStart(target);
			m_checkHideObj = target;
			m_moveFunc = &TargetProbe::TargetMove;
		}
	}

	void TargetProbe::EndInvestigateHideAnimation() {
		//AnimatorのExitFuncで呼び出すからステートが違う場合は処理をしないようにする。
		//もしバグが生じるようなら、こちらのUpdateでアニメーションの終了を監視するようにする。
		auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
		if (enemy) {
			//TargetProbe状態で無かったら処理をしない。
			if (!enemy->IsEqualStateType<EnState_ProbTarget>()) {
				return;
			}
		}

		m_probCount++;

		if (m_probCount >= m_numPorb) {  //指定回数調べたら。
			m_moveFunc = nullptr;
			//ChangeState<EnState_LoseTarget>();
		}
		else {  //まだカウントが過ぎていなかったら。
			SetHideObjCollisionUpdate(true);
			SetAstarRondomHideObject();  //もう一度調べる。
		}
	}

	void TargetProbe::ExitProbState() {
		//SetHideObjCollisionUpdate(true);
		RemoveNode();
	}
}

//endbasecross