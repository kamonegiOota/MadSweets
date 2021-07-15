/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	namespace maru
	{

		template<class T>//,
			//enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >  //GameObject‚ğŒp³‚µ‚½‚à‚Ì‚Ì‚İw’è‚Å‚«‚é
			//enable_if_t<is_base_of_v<BaseEnemy, T>, std::nullptr_t> = nullptr>  //BaseEnemy‚ğŒp³‚µ‚½•¨‚Ì‚İw’è‚Å‚«‚é
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