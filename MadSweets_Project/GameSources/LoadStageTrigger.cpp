/*!
@file LoadData.cpp
@brief LoadDataのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "LoadStageTrigger.h"

#include "PlayerProvider.h"
#include "DebugObject.h"

#include "AlphaFadeObject.h"
#include "MainStage.h"

#include "DebugObject.h"

#include "MyUtility.h"

#include "PlayerStatusManager.h"
#include "PlayerWeightManager.h"
#include "PlayerCalorieManager.h"

namespace basecross {

	LoadStageTrigger::SavingValue LoadStageTrigger::sm_saveValue = SavingValue();

	void LoadStageTrigger::ChangeStageReserve() {
		MainStage::SetCreatePlayerPosition(m_position);
		MainStage::SetMapName(m_nextMap);

		auto player = maru::MyUtility::GetGameObject<PlayerObject>();
		auto status = player->GetComponent<PlayerStatusManager>(false);
		auto weightMgr = player->GetComponent<PlayerWeightManager>(false);
		auto calorie = player->GetComponent<PlayerCalorieManager>(false);

		if (status && weightMgr && calorie) {
			sm_saveValue.hp = status->GetHP();
			sm_saveValue.weight = weightMgr->GetWeight();
			sm_saveValue.weightState = weightMgr->GetState();
			sm_saveValue.calorie = calorie->GetNowCalorie();
			sm_saveValue.isActive = true;
		}
	}

	void LoadStageTrigger::MovePosition() {
		if (m_target) {
			auto trans = m_target->GetComponent<Transform>();
			trans->SetPosition(m_position);
			trans->SetForward(Vec3(1.0f,0.0f,0.0f));
		}
	}

	void LoadStageTrigger::ChangeStage() {
		auto stage = dynamic_pointer_cast<MainStage>(GetStage());
		if (stage) {
			//MovePosition();
			//stage->ChangeMap(m_nextMap, m_fadeCtrl.GetShard());
			ChangeStageReserve();
			float stayTime(0.0f); //ステージ遷移する場合に待つ時間
			PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
		}
		else {
			DebugObject::sm_wss << endl << L"LoadStageTrigger :: MargeTestStageが存在しません。";
		}
	}

	void LoadStageTrigger::FadeStart() {
		m_fadeCtrl->AddEndAction(GetThis<LoadStageTrigger>(), &LoadStageTrigger::ChangeStage);
		m_fadeCtrl->FadeOutStart();
	}

	void LoadStageTrigger::OnCreate() {
		auto col = GetGameObject()->AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		m_fadeCtrl = GetStage()->Instantiate<AlphaFadeObject>()->GetComponent<AlphaFadeCtrl>();
	}

	void LoadStageTrigger::OnCollisionEnter(std::shared_ptr<GameObject>& other){
		auto player = other->GetComponent<PlayerProvider>(false);
		if (player) {
			m_target = other;
			FadeStart();
		}
	}

}

//endbacecross