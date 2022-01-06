/*!
@file CrackCookie.cpp
@brief CrackCookie�N���X����
�S���F�ێR�T��
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
		//�����d���ɂ���ď����󂯂�_���[�W���ς�鎞�p�̊֐�
		//���݂�1.0f����̂�
		return 1.0f;
	}

	void CrackCookie::DestProcess() {
		//�{�������ŗ���������B����鏈���������
		GetGameObject()->SetUpdateActive(false);
		GetGameObject()->SetDrawActive(false);
	}

	void CrackCookie::TextureCheck() {
		auto prob = m_durability / m_maxDurability;
		if (prob <= 0.5f) {  //�ϋv�l�������ɂȂ�����B
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
		if (m_durability <= 0.0f) {  //��ꂽ��ԂȂ珈�������Ȃ��B
			return;
		}

		auto weightMgr = other->GetComponent<PlayerWeightManager>(false);
		if (weightMgr) {
			//�����Ă�����
			if (weightMgr->GetState() == WeightState::Chubby) {
				auto damage = CalucDamage(weightMgr);
				Crack(damage);
			}
		}
	}
	
}

//endbasecross