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
		Vec3 m_direct; //向きたい方向

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