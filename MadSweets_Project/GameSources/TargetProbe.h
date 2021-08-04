/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// �^�[�Q�b�g��{������R���|�[�l���g
	/// </summary>
	class TargetProbe : public Component, public BaseUseVelocity
	{
		std::shared_ptr<GameObject> m_target;

		//����v���C���[�̑{�������邩�H
		int m_numPorb = 2;
		int m_probCount = 0;  //���ۂɑ{�������񐔁B

		//Astar�ɑ{������Z�b�g����B
		void SetAstarRondomHideObject();

		void ChangeState();
		void RouteEnd();
		void Move();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //�{���J�n

		//�A�N�Z�b�T--------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}
	};

}

//endbasecorss