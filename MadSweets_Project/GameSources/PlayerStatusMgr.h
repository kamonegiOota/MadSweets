/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "I_Damaged.h"

namespace basecross {

	enum class PlayerState {
		Nomal,
		Dest, //���S���
		Destroy, //���S���o���I�����Ċ��S�Ɏ��񂾏�ԁB
	};

	struct PlayerStatusParam {
		float hp = 10.0f;
		PlayerState state = PlayerState::Nomal;
	};

	class PlayerStatusMgr : public Component , public I_Damaged
	{
		PlayerStatusParam m_param;

	public:
		PlayerStatusMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		 
		void OnCreate() override{}
		void OnUpdate() override{}

		//�C���^�[�t�F�[�X�̎���
		void Damage(const float& damage) override;

		//�A�N�Z�b�T---------------------------------------------------------
		void ChangeState(const PlayerState& state) {
			m_param.state = state;
		}
		PlayerState GetState() const {
			return m_param.state;
		}

	};

}

//endbasecross