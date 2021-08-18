/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class WallEvasionTactile : public Component
	{
		vector<std::function<void(const std::shared_ptr<GameObject>& other)>> m_excuteActions;

	public:
		WallEvasionTactile(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr)
		{}

		void OnCreate() override;

		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;

		
		//�A�N�Z�b�T-----------------------------------------------------------
		void AddExcuteAction(const std::function<void(const std::shared_ptr<GameObject>& other)>& enterAction) {
			m_excuteActions.push_back(enterAction);
		}
	};

}

//endbasecross