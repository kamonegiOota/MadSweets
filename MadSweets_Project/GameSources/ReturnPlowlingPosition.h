/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// �p�j��Ԃ̏ꏊ�܂Ŗ߂�R���|�[���l���g
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
		/// �߂鏈���J�n
		/// </summary>
		void StartReturn();
	};

}

//endbasecross