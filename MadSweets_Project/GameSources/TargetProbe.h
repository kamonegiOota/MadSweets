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
		std::shared_ptr<GameObject> m_target;  //�{���Ώ�
		std::shared_ptr<GameObject> m_checkHideObj;  //�`�F�b�N���Ă���B���I�u�W�F�N�g

		std::function<void(TargetProbe&)> m_moveFunc;

		//����v���C���[�̑{�������邩�H
		int m_numPorb = 1;
		int m_probCount = 0;  //���ۂɑ{�������񐔁B

		float m_searchRange = 20.0f;  //�T������͈�

		//Astar�ɑ{������Z�b�g����B
		void SetAstarRondomHideObject();

		void ChangeState();
		void RouteEnd();

		void TargetMove();
		void AstarMove();

		void ResetProbe();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //�{���J�n
		void StartProb(const shared_ptr<GameObject>& target);  //�{���J�n

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