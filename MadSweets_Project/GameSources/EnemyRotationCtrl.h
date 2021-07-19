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
		Vec3 m_direct; //������������

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