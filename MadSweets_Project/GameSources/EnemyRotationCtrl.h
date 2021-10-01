/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrlなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class EnemyRotationCtrl : public Component
	{
		Vec3 m_direct = Vec3(0.0f); //向きたい方向
		float m_speed = 0.25f;

		Quat CalcuRotationQuat(Vec3 direct, const float& speed);
		void RotationProcess();

	public:
		EnemyRotationCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//アクセッサ------------------------------------------------------------------

		void SetDirect(const Vec3& direct) {
			m_direct = direct;
		}
	};

}

//endbasecross