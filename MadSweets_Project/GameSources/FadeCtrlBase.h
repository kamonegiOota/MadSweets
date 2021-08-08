/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	using itbs::Utility::Delegate;

	class FadeCtrlBase : public Component
	{
	protected:
		Delegate<void()> m_endAction;  //フェード終了時に行いたい関数を登録。

	public:

		FadeCtrlBase(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		virtual void FadeStart() = 0;

		//アクセッサ-----------------------------------------------------------
		virtual void SetEndAction(const Delegate<void()>& action) final {
			m_endAction = action;
		}

		template<class Obj>
		void AddEndAction(shared_ptr<Obj>& objPtr, void(Obj::* func)()) {
			m_endAction.AddFunc(objPtr, func);
		}

	};

}

//endbasecross