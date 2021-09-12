/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// 徘徊状態の場所まで戻るコンポーンネント
	/// </summary>
	class ReturnPlowlingPosition : public Component , public BaseUseVelocity
	{
		ex_weak_ptr<AstarCtrl> m_astar;

		void ChangeStateMachine();
		void Move();
		void Rotation(const Vec3& moveVec);

	public:

		ReturnPlowlingPosition(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/// <summary>
		/// 戻る処理開始
		/// </summary>
		void StartReturn();
	};

}

//endbasecross