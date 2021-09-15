/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrlなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	/// <summary>
	/// 現在のOwnerがターゲットに指定しているオブジェクトを管理し、他のコンポーネントと共有する。
	/// </summary>
	class TargetMgr : public Component
	{
		std::weak_ptr<GameObject> m_target;

	public:

		TargetMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//アクセッサ-------------------------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			auto target = m_target.lock();
			return target ? target : nullptr;
		}
	};

}

//basecross