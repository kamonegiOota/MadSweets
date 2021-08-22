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
#include "MargeTestStage.h"

namespace basecross {

	void LoadStageTrigger::ChangeStage() {
		//float stayTime(0.0f); //ステージ遷移する場合に待つ時間
		//PostEvent(stayTime, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMargeTestStage");
		auto stage = dynamic_pointer_cast<MargeTestStage>(GetStage());
		if (stage) {
			stage->ChangeMap(m_nextMap, m_fadeCtrl.GetShard());
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
			FadeStart();
		}
	}

}

//endbacecross