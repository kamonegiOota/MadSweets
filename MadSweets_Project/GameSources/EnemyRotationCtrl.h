/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrl�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class EnemyRotationCtrl : public Component
	{
		Vec3 m_direct = Vec3(0.0f); //������������
		float m_speed = 0.25f;

		Quat CalcuRotationQuat(Vec3 direct, const float& speed);
		void RotationProcess();

	public:
		EnemyRotationCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//�A�N�Z�b�T------------------------------------------------------------------

		void SetDirect(const Vec3& direct) {
			m_direct = direct;
		}
	};

}

//endbasecross