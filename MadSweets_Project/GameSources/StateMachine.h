/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	namespace maru
	{

		template<class T>//,
			//enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >  //GameObject���p���������̂̂ݎw��ł���
			//enable_if_t<is_base_of_v<BaseEnemy, T>, std::nullptr_t> = nullptr>  //BaseEnemy���p���������̂ݎw��ł���
		class StateMachine
		{
			std::weak_ptr<T> m_owner;

		protected:

			std::shared_ptr<T> GetOwner() {
				auto owner = m_owner.lock();
				if (owner) {
					return owner;
				}
				return nullptr;
			}

		public:
			StateMachine(const std::shared_ptr<T>& owner) :
				m_owner(owner)
			{}

			virtual void OnStart() = 0;
			virtual void OnUpdate() = 0;
			virtual void OnExit() = 0;

		};

	}

}

//endbasecross