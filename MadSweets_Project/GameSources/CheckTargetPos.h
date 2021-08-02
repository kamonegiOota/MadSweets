/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"
#include "BaseUseVelocity.h"

namespace basecross {

	class CheckTargetPos : public Component, public BaseUseVelocity 
	{
		//Vec3 m_targetPos;

		void Move();
		void ChangeStateMachine();

	public:

		CheckTargetPos(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//アクセッサ--------------------------------------------------------------
		//void SetTargetPos(const Vec3& position) {
		//	m_targetPos = position;
		//}
		//Vec3 GetTargetPos() const {
		//	return m_targetPos;
		//}

	};

}

//endbasecross