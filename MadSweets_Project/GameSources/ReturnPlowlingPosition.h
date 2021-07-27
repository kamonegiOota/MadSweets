/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"

namespace basecross {

	//徘徊状態の場所まで戻るコンポーンネント
	class ReturnPlowlingPosition : public Component
	{
		ex_weak_ptr<AstarCtrl> m_astar;
		float m_speed;

		void ChangeStateMachine();
		void Move();
		void Rotation(const Vec3& moveVec);

	public:

		ReturnPlowlingPosition(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr),
			m_speed(2.0f)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartReturn(); //戻る処理開始
	};

}

//endbasecross