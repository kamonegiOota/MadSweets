
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

namespace basecross {


	void SoundCookie::SendListener() {
		auto ears = maru::MyUtility::GetComponents<EnemyEar>();
		for (auto& ear : ears) {
			ear->SoundListen(transform->GetPosition());
		}
	}

	void SoundCookie::MakeSound() {
		//音を出す

		//音を聞くものに渡す
		SendListener();
	}

	void SoundCookie::Crack() {
		m_numCrack--;

		if (m_numCrack < 0) {
			m_numCrack = 0;
		}
	}

	void SoundCookie::OnCreate() {
		
	}

	void SoundCookie::OnUpdate() {
		
	}

	void SoundCookie::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (m_numCrack == 0) {
			return;
		}

		auto player = other->GetComponent<PlayerProvider>(false);
		if (player) {
			MakeSound();
			Crack();
		}
	}

}

//endbasecross