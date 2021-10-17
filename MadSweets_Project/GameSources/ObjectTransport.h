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
		Vec3 m_offset = Vec3(0.0f);
		std::weak_ptr<GameObject> m_target;  //�^�ԑΏ�

		void ParentSet();  //�^�[�Q�b�g���������g�̎q�I�u�W�F�N�g�ɂ���B
		void Move();  //�ړ�������������B

	public:
		ObjectTransport(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//�A�N�Z�b�T----------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
			ParentSet();
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