/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	class WallEvasionTactile : public Component
	{
		using ActionFunc = std::function<void(const std::shared_ptr<WallEvasionTactile>& tactile, const std::shared_ptr<GameObject>& other)>;

		vector<ActionFunc> m_excuteActions;

	public:
		WallEvasionTactile(const std::shared_ptr<GameObject>& objPtr) 
			:Component(objPtr)
		{}

		void OnCreate() override;

		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;

		
		//アクセッサ-----------------------------------------------------------
		void AddExcuteAction(const ActionFunc& enterAction) {
			m_excuteActions.push_back(enterAction);
		}
	};

}

//endbasecross