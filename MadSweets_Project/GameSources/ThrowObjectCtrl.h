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

	public:
		ThrowObjectCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override{}
		void OnUpdate() override{}

		void Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed);

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;


		//�A�N�Z�b�T------------------------------------------------------------
		void SetOwner(const std::shared_ptr<GameObject>& owner) {
			m_owner = owner;
		}
	};

}

//endbasecross