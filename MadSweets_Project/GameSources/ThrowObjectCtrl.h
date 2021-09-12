/*!
@file SearchObject.h
@brief SearchObject�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// ������ꂽ�I�u�W�F�N�g�̃R���g���[��
	/// </summary>
	class ThrowObjectCtrl : public Component
	{
		std::shared_ptr<GameObject> m_owner;
		float m_attackPower;

		void Rotation(const Vec3& direct);

	public:
		ThrowObjectCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr), m_attackPower(2.0f)
		{}

		void OnCreate() override{}
		void OnStart() override{}
		void OnUpdate() override{}

		/// <summary>
		/// ������Ƃ��̊֐�
		/// </summary>
		/// <param name="owner">�������I�u�W�F�N�g</param>
		/// <param name="direct">���������</param>
		/// <param name="speed">���ł����X�s�[�h</param>
		void Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed);

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;


		//�A�N�Z�b�T------------------------------------------------------------

		void SetOwner(const std::shared_ptr<GameObject>& owner) {
			m_owner = owner;
		}
	};

}

//endbasecross