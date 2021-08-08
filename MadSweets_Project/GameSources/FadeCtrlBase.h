/*!
@file MyUtility.h
@brief MyUtility�N���X
�S���F�ێR�T��
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
		Delegate<void()> m_endAction;  //�t�F�[�h�I�����ɍs�������֐���o�^�B

	public:

		FadeCtrlBase(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		virtual void FadeStart() = 0;

		//�A�N�Z�b�T-----------------------------------------------------------
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