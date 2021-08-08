/*!
@file MaruStage.h
@brief MaruStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	using itbs::Utility::Delegate;

	class TitleNameCtrl : public Component
	{
		Delegate<void()> m_delegate;

		ex_weak_ptr<UIObject> m_fontUI;
		ex_weak_ptr<UIObject> m_chocoUI;

		float m_speed = 1.0f;
		bool m_isEnd = false;

		std::function<void(TitleNameCtrl&)> m_updateFunc;

		void UpdateChoco();

	public:

		TitleNameCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<UIObject>& fontUI,
			const std::shared_ptr<UIObject>& chocoUI
		) :
			Component(objPtr),m_fontUI(fontUI),m_chocoUI(chocoUI)
		{}

		void OnCreate() override;
		void OnUpdate() override;


		//�A�N�Z�b�T----------------------------------------------------------------
		void FadeStart();

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}

		bool IsEnd() const {
			return m_isEnd;
		}

		void SetDelegate(const Delegate<void()>& deleg) {
			m_delegate = deleg;
		}

		template<class Obj>
		void AddDelegateFunc(const std::shared_ptr<Obj>& obj, void(Obj::* fn)()) {

		}
	};

}

//endbasecross