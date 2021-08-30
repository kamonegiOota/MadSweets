/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "I_Damaged.h"

namespace basecross {

	enum class PlayerStaus {
		Nomal,
		Dest, //���S���
		Destroy, //���S���o���I�����Ċ��S�Ɏ��񂾏�ԁB
	};

	struct PlayerStatusParam {
		float hp = 10.0f;
		float maxHp = hp;
		PlayerStaus state = PlayerStaus::Nomal;
	};

	/// <summary>
	/// player�̃X�e�[�^�X�̃R���|�[�l���g
	/// </summary>
	class PlayerStatusMgr : public Component , public I_Damaged
	{
		PlayerStatusParam m_param;

		void ChangeGameOverStage();
		void DestProcess();

	public:
		PlayerStatusMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		 
		void OnCreate() override{}
		void OnUpdate() override;

		//�C���^�[�t�F�[�X�̎���
		void Damage(const float& damage) override;

		//�A�N�Z�b�T---------------------------------------------------------
		void ChangeState(const PlayerStaus& state) {
			m_param.state = state;
		}
		PlayerStaus GetState() const {
			return m_param.state;
		}

		void AddHP(const float& value) {
			m_param.hp += value;
		}

		float GetHP() const {
			return m_param.hp;
		}

		float GetMaxHp() const {
			return m_param.maxHp;
		}
		
		//HP�̊������v�Z���ĕԂ�
		float CalucHPRatio() const{
			return m_param.hp / m_param.maxHp;
		}

	};

}

//endbasecross