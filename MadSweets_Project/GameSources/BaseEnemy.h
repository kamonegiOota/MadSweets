/*!
@file BaseEnemy.h
@brief BaseEnemy
担当者：丸山 裕喜
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
		/// ステートマシンの変更
		/// </summary>
		/// <param name="newState">変更したいステート</param>
		virtual void ChangeStateMachine(const std::shared_ptr<maru::StateMachine<BaseEnemy>>& newState);
	};

}

//endbasecross