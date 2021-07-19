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
		/// <summary>
		/// 同じステートに変更仕様とした場合trueを返す
		/// </summary>
		/// <returns>同じステートの場合true</returns>
		template<class T>
		bool IsEqualStateType() {  
			auto t = dynamic_pointer_cast<T>(m_stateMachine);
			if (t) {
				return true;
			}
			else {
				return false;
			}
		}

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
		template<class T, class... Ts,
			enable_if_t<is_base_of_v<maru::StateMachine<BaseEnemy>, T>, std::nullptr_t> = nullptr >
		void ChangeStateMachine(Ts&&... params) {
			if (IsEqualStateType<T>()) {  //同じステートに変更しようとした場合処理をしない。
				return;
			}

			auto newState = make_shared<T>(GetThis<BaseEnemy>(),params...);

			if (m_stateMachine) {
				m_stateMachine->OnExit();
			}

			newState->OnStart();
			m_stateMachine = newState;
		}
	};

}

//endbasecross