/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "CrackCookie.h"
#include "PlayerProvider.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void CrackCookie::DestProcess() {
		//�{�������ŗ���������B����鏈���������
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
		if (m_durability <= 0.0f) {  //��ꂽ��ԂȂ珈�������Ȃ��B
			return;
		}

		auto player = other->GetComponent<PlayerProvider>(false);
		if (player) {
			//�{�������Ń_���[�W�̌v�Z��A����邩�ǂ����̔��f������B

			Crack(1.0f);
		}
	}
	
}

//endbasecross