/*!
@file ObjectTransport.h
@brief ObjectTransport
�S���ҁF�ێR �T��
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// �I�u�W�F�N�g���^�ԃR���|�[�l���g
	/// </summary>
	class ObjectTransport : public Component
	{
		Vec3 m_offset = Vec3(0.0f, 0.1f, 0.0f);
		float m_targetScaleAdjust = 0.5f;
		std::weak_ptr<GameObject> m_target;  //�^�ԑΏ�

		void Move();  //�ړ�������������B
		void Rotation();

		void ScaleAdjust(const std::shared_ptr<GameObject>& target);

	public:
		ObjectTransport(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//�A�N�Z�b�T----------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
			ScaleAdjust(target);
		}
		std::shared_ptr<GameObject> GetTarget() const {
			auto target = m_target.lock();
			return target;
		}

		void SetOffset(const Vec3& offset) {
			m_offset = offset;
		}
		Vec3 GetOffset() const {
			return m_offset;
		}

		void SetTargetScaleAdjust(const float& adjust) {
			m_targetScaleAdjust = adjust;
			ScaleAdjust(m_target.lock());
		}

		/// <summary>
		/// �^�[�Q�b�g�����݂��邩�ǂ���
		/// </summary>
		/// <returns>�^�[�Q�b�g�����݂��Ȃ��Ȃ�true</returns>
		bool IsTargetEmpty() {
			auto target = m_target.lock();
			return target == nullptr ? true : false;
		}

	};

}

//endbasecross