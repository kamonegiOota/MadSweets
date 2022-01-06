/*!
@file TactileCtrl.h
@brief TactileCtrl
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	class TactileCtrl : public Component
	{
		//Updateで呼び出す関数ポインタの型
		using ActionFunc = std::function<void(const std::shared_ptr<TactileCtrl>& tactile, const std::shared_ptr<GameObject>& other)>;

		vector<ActionFunc> m_excuteActions;

	public:
		TactileCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;

		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;

		
		//アクセッサ-----------------------------------------------------------

		/// <summary>
		/// アップデートで呼び出す関数ポインタをセットする
		/// </summary>
		/// <param name="excuteAction">アップデートで呼び出す関数ポインタ</param>
		void AddExcuteAction(const ActionFunc& excuteAction) {
			m_excuteActions.push_back(excuteAction);
		}
	};

}

//endbasecross