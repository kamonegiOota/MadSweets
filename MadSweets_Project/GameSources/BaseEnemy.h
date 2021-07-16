/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"

namespace basecross {

	class BaseEnemy :public Component
	{
	protected:
	 	std::shared_ptr<maru::StateMachine<BaseEnemy>> m_stateMachine;

	public:
		BaseEnemy(const std::shared_ptr<GameObject>& objPtr);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnDraw() override {}

		/// <summary>
		/// �X�e�[�g�}�V���̕ύX
		/// </summary>
		/// <param name="newState">�ύX�������X�e�[�g</param>
		virtual void ChangeStateMachine(const std::shared_ptr<maru::StateMachine<BaseEnemy>>& newState);
	};

}

//endbasecross