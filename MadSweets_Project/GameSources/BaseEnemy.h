/*!
@file BaseEnemy.h
@brief BaseEnemy
�S���ҁF�ێR �T��
*/

#pragma once

#include "StateMachine.h"
#include "EnemyStateNodeBase.h"

namespace basecross {

	class BaseEnemy :public Component
	{

	protected:
	 	std::shared_ptr<EnemyStateNodeBase<BaseEnemy>> m_stateMachine;
		wstring m_mapType = L"";  //�ǂ̃}�b�v�ɏ������Ă��邩�H

	public:
		BaseEnemy(const std::shared_ptr<GameObject>& objPtr);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void OnDraw() override {}


		//�A�N�Z�b�T--------------------------------------------------------------

		void SetMapType(const wstring& type) {
			m_mapType = type;
		}
		wstring GetMapType() const {
			return m_mapType;
		}

		/// <summary>
		/// �X�e�[�g�}�V���̕ύX
		/// </summary>
		/// <param name="newState">�ύX�������X�e�[�g</param>
		//template<class T, class... Ts,
		//	enable_if_t<is_base_of_v<EnemyStateNodeBase<BaseEnemy>, T>, std::nullptr_t> = nullptr >
		//void ChangeStateMachine(Ts&&... params) {
		//	if (IsEqualStateType<T>()) {  //�����X�e�[�g�ɕύX���悤�Ƃ����ꍇ���������Ȃ��B
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
		/// �����X�e�[�g�ł��ύX���������������Ƃ��͂�����𗘗p
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

	};

}

//endbasecross