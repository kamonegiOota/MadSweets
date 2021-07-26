/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// �^�[�Q�b�g��{������R���|�[�l���g
	/// </summary>
	class TargetProbe : public Component
	{
		std::shared_ptr<GameObject> m_target;

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}


		//�A�N�Z�b�T--------------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

	};

}

//endbasecorss