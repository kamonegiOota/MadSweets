
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "SoundCookie.h"
#include "PlayerProvider.h"

#include "MyUtility.h"
#include "EnemyEar.h"

#include "PNTPointDraw.h"

#include "DebugObject.h"

namespace basecross {

	void SoundCookie::DestProcess() {
		//�{���͕��X�̏�Ԃɂ���B
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
		//�����o��

		//���𕷂����̂ɓn��
		SendListener();
	}

	void SoundCookie::Crack() {
		m_numCrack--;

		if (m_numCrack <= 0) {
			m_numCrack = 0;
			DestProcess();
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