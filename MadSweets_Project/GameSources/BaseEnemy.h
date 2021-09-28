/*!
@file BaseEnemy.h
@brief BaseEnemy
担当者：丸山 裕喜
*/

#pragma once

#include "StateMachine.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	class BaseEnemy :public Component
	{

	protected:
	 	std::shared_ptr<EnemyStateNodeBase<BaseEnemy>> m_stateMachine;
		wstring m_mapType = L"";  //どのマップに所属しているか？

	public:
		BaseEnemy(const std::shared_ptr<GameObject>& objPtr);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnDraw() override {}


		//アクセッサ--------------------------------------------------------------

		void SetMapType(const wstring& type) {
			m_mapType = type;
		}
		wstring GetMapType() const {
			return m_mapType;
		}

		/// <summary>
		/// ステートマシンの変更
		/// </summary>
		/// <param name="newState">変更したいステート</param>
		//template<class T, class... Ts,
		//	enable_if_t<is_base_of_v<EnemyStateNodeBase<BaseEnemy>, T>, std::nullptr_t> = nullptr >
		//void ChangeStateMachine(Ts&&... params) {
		//	if (IsEqualStateType<T>()) {  //同じステートに変更しようとした場合処理をしない。
		//		return;
		//	}

		//	auto newState = make_shared<T>(GetThis<BaseEnemy>(),params...);

		//	if (m_stateMachine) {
		//		m_stateMachine->OnExit();
		//	}

		//	newState->OnStart();
		//	m_stateMachine = newState;
		//}

		/// <summary>
		/// 同じステートでも変更処理を加えたいときはこちらを利用
		/// </summary>
		template<class T, class... Ts,
			enable_if_t<is_base_of_v<EnemyStateNodeBase<BaseEnemy>, T>, std::nullptr_t> = nullptr >
		void AbsoluteChangeStateMachine(Ts&&... params) 
		{

			auto newState = make_shared<T>(GetThis<BaseEnemy>(), params...);

			if (m_stateMachine) {
				m_stateMachine->OnExit();
			}

			newState->OnStart();
			m_stateMachine = newState;
		}

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

	};

}

//endbasecross