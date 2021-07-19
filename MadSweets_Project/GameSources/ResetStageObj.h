
/*!
@file GameManager.h
@brief GameManager�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"
//#include "AdvanceComponent.h"

namespace basecross {

	class ResetStageObj : public Component
	{
		Vec3 m_scale;
		Vec3 m_rotation;
		Quat m_quat;
		Vec3 m_position;

	public:

		ResetStageObj(const std::shared_ptr<GameObject>& objPtr)
			:
			Component(objPtr),
			m_scale(Vec3(1.0f)),
			m_rotation(Vec3(0.0f)),
			m_quat(Quat(0.0f)),
			m_position(Vec3(0.0f))
		{

		}

		void OnCreate() override;
		void OnUpdate() override {}


		void ResetAll();  //�S�ă��Z�b�g
		void ResetUpdate();
		void ResetSRP();  //�X�P�[���A���[�e�[�V�����A�|�W�V���������Z�b�g����B



		//�A�N�Z�b�T
		void SetScale(const Vec3& scale){
			m_scale = scale;
		}

		void SetQuatermion(const Quat& quat) {
			m_quat = quat;
		}

		Quat GetQuatermion() const {
			return m_quat;
		}

		void SetRotation(const Vec3& rotation) {
			m_rotation = rotation;
		}

		void SetPosition(const Vec3& position) {
			m_position = position;
		}

		Vec3 GetPosition() const {
			return m_position;
		}

		void SetSRP(){  //�X�P�[���A���[�e�[�V�����A�|�W�V�������Z�b�g����B
			auto objTrans = GetGameObject()->GetComponent<Transform>();

			m_scale = objTrans->GetScale();
			m_rotation = objTrans->GetRotation();
			m_quat = objTrans->GetQuaternion();
			m_position = objTrans->GetPosition();
		}
	};

}

//endbasecross