/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "CrackCookie.h"
#include "PlayerProvider.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void CrackCookie::DestProcess() {
		//本来ここで落っこちる。崩れる処理も入れる
		GetGameObject()->SetUpdateActive(false);
		GetGameObject()->SetDrawActive(false);
	}

	void CrackCookie::Crack(const float& damage) {
		m_durability += -damage;

		if (m_durability <= 0.0f) {
			m_durability = 0.0f;
			DestProcess();
		}
	}

	void CrackCookie::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (m_durability <= 0.0f) {  //壊れた状態なら処理をしない。
			return;
		}

		auto player = other->GetComponent<PlayerProvider>(false);
		if (player) {
			//本来ここでダメージの計算や、崩れるかどうかの判断をする。

			Crack(1.0f);
		}
	}
	
}

//endbasecross