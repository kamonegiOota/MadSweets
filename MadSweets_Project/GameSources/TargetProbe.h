/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// ターゲットを捜索するコンポーネント
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


		//アクセッサ--------------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

	};

}

//endbasecorss