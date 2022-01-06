
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "SoundCookie.h"
#include "PlayerProvider.h"

#include "MyUtility.h"
#include "EnemyEar.h"

#include "PNTPointDraw.h"
#include "SoundHelper.h"

#include "DebugObject.h"
#include "PlayerWeightManager.h"

namespace basecross {

	void SoundCookie::TextureCheck() {
		float prob = (float)m_numCrack / (float)m_maxNumCrack;
		if (prob <= 0.5f) {  //耐久値が半分になったら。
			GetGameObject()->GetComponent<BcBaseDraw>()->SetTextureResource(m_textures[(int)CrackState::Crack]);
		}
	}

	void SoundCookie::DestProcess() {
		//本来は粉々の状態にする。
		GetGameObject()->SetUpdateActive(false);
		GetGameObject()->SetDrawActive(false);
	}

	void SoundCookie::SendListener() {
		auto ears = maru::MyUtility::GetComponents<EnemyEar>();
		for (auto& ear : ears) {
			ear->Listen(transform->GetPosition());
		}
	}

	void SoundCookie::MakeSound() {
		//音を出す
		SimpleSoundManager::OnePlaySE(L"CookieCrushSE");

		//音を聞くものに渡す
		SendListener();
	}

	void SoundCookie::Crack() {
		m_numCrack--;
		TextureCheck();

		if (m_numCrack <= 0) {
			m_numCrack = 0;
			DestProcess();
		}
	}

	void SoundCookie::OnCreate() {
		m_textures = {
			{L"Cokie_Tx"},
			{L"Cokie_Crack_Tx"},
			{L"Cokie_Crack_Last_Tx"},
		};

		GetGameObject()->GetComponent<BcBaseDraw>()->SetTextureResource(m_textures[(int)CrackState::Normal]);
	}

	void SoundCookie::OnUpdate() {
		
	}

	void SoundCookie::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (m_numCrack == 0) {
			return;
		}

		auto weightMgr = other->GetComponent<PlayerWeightManager>(false);
		if (weightMgr) {
			//太っていたら
			if (weightMgr->GetState() == WeightState::Chubby) {
				MakeSound();
				Crack();
			}
		}
	}

}

//endbasecross