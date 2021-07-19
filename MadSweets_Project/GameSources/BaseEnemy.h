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
		/// <summary>
		/// �����X�e�[�g�ɕύX�d�l�Ƃ����ꍇtrue��Ԃ�
		/// </summary>
		/// <returns>�����X�e�[�g�̏ꍇtrue</returns>
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
		/// �X�e�[�g�}�V���̕ύX
		/// </summary>
		/// <param name="newState">�ύX�������X�e�[�g</param>
		template<class T, class... Ts,
			enable_if_t<is_base_of_v<maru::StateMachine<BaseEnemy>, T>, std::nullptr_t> = nullptr >
		void ChangeStateMachine(Ts&&... params) {
			if (IsEqualStateType<T>()) {  //�����X�e�[�g�ɕύX���悤�Ƃ����ꍇ���������Ȃ��B
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