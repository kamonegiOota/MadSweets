/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "AstarCtrl.h"

namespace basecross {

	//�p�j��Ԃ̏ꏊ�܂Ŗ߂�R���|�[���l���g
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

		void StartReturn(); //�߂鏈���J�n
	};

}

//endbasecross