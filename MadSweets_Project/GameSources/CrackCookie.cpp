/*!
@file CrackCookie.cpp
@brief CrackCookieクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "CrackCookie.h"
#include "PlayerProvider.h"

#include "MyUtility.h"

#include "DebugObject.h"

#include"SoundHelper.h"	

namespace basecross {

	float CrackCookie::CalucDamage(const std::shared_ptr<PlayerWeightManager>& weightMgr) {
		//将来重さによって床が受けるダメージが変わる時用の関数
		//現在は1.0f減るのみ
		return 1.0f;
	}

	void CrackCookie::DestProcess() {
		//本来ここで落っこちる。崩れる処理も入れる
		GetGameObject()->SetUpdateActive(false);
		GetGameObject()->SetDrawActive(false);
	}

	void CrackCookie::TextureCheck() {
		auto prob = m_durability / m_maxDurability;
		if (prob <= 0.5f) {  //耐久値が半分になったら。
			GetGameObject()->GetComponent<BcBaseDraw>()->SetTextureResource(m_textures[(int)CrackState::Crack]);
		}
	}

	void CrackCookie::Crack(const float& damage) {
		m_durability += -damage;

		if (m_durability <= 0.0f) {
			m_durability = 0.0f;
			DestProcess();
		}

		TextureCheck();

		SimpleSoundManager::OnePlaySE(L"CookieCrushSE");
	}

	void CrackCookie::OnCreate() {
		m_textures = {
			{L"Cokie_Tx"},
			{L"Cokie_Crack_Tx"},
			{L"Cokie_Crack_Last_Tx"},
		};

		GetGameObject()->GetComponent<BcBaseDraw>()->SetTextureResource(m_textures[(int)CrackState::Normal]);
	}

	void CrackCookie::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (m_durability <= 0.0f) {  //壊れた状態なら処理をしない。
			return;
		}

		auto weightMgr = other->GetComponent<PlayerWeightManager>(false);
		if (weightMgr) {
			//太っていたら
			if (weightMgr->GetState() == WeightState::Chubby) {
				auto damage = CalucDamage(weightMgr);
				Crack(damage);
			}
		}
	}
	
}

//endbasecross