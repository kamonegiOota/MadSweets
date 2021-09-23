/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrl�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	/// <summary>
	/// ���݂�Owner���^�[�Q�b�g�Ɏw�肵�Ă���I�u�W�F�N�g���Ǘ����A���̃R���|�[�l���g�Ƌ��L����B
	/// </summary>
	class TargetMgr : public Component
	{
		std::weak_ptr<GameObject> m_target;

	public:

		TargetMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//�A�N�Z�b�T-------------------------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			auto target = m_target.lock();
			return target ? target : nullptr;
		}
	};

}

//basecross