/*!
@file TargetManager.h
@brief TargetManagerなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	/// <summary>
	/// 現在のOwnerがターゲットに指定しているオブジェクトを管理し、他のコンポーネントと共有する。
	/// </summary>
	class TargetManager : public Component
	{
		std::weak_ptr<GameObject> m_target;

	public:

		TargetManager(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		
		TargetManager(const std::shared_ptr<GameObject>& objPtr,const std::shared_ptr<GameObject>& target)
			:Component(objPtr), m_target(target)
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
			//return m_target;
		}
	};

}

//basecross