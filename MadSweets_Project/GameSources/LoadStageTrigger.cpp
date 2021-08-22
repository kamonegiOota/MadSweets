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

#include "DebugObject.h"

namespace basecross {

	void LoadStageTrigger::ChangeStage() {
		auto stage = dynamic_pointer_cast<MargeTestStage>(GetStage());
		if (stage) {
			DebugObject::sm_wss << endl <<L"LoadStageTrigger :: MargeTestStageが存在しません。";
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