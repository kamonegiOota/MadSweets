/*!
@file TactileCtrl.h
@brief TactileCtrl
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	class TactileCtrl : public Component
	{
		//Update�ŌĂяo���֐��|�C���^�̌^
		using ActionFunc = std::function<void(const std::shared_ptr<TactileCtrl>& tactile, const std::shared_ptr<GameObject>& other)>;

		vector<ActionFunc> m_excuteActions;

	public:
		TactileCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;

		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;

		
		//�A�N�Z�b�T-----------------------------------------------------------

		/// <summary>
		/// �A�b�v�f�[�g�ŌĂяo���֐��|�C���^���Z�b�g����
		/// </summary>
		/// <param name="excuteAction">�A�b�v�f�[�g�ŌĂяo���֐��|�C���^</param>
		void AddExcuteAction(const ActionFunc& excuteAction) {
			m_excuteActions.push_back(excuteAction);
		}
	};

}

//endbasecross