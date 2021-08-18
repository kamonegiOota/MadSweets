/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
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

		
		//アクセッサ-----------------------------------------------------------
		void AddExcuteAction(const std::function<void(const std::shared_ptr<GameObject>& other)>& enterAction) {
			m_excuteActions.push_back(enterAction);
		}
	};

}

//endbasecross