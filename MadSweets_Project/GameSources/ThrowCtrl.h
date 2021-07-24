/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "ThrowObjectCtrl.h"

namespace basecross {

	/// <summary>
	/// 投げる動作のコントロール
	/// </summary>
	class ThrowCtrl : public Component
	{

	public:

		ThrowCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		template<class T,
			enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
		void Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed = 1.0f)
		{
			auto createPos = transform->GetPosition();

			auto newObj = GetStage()->Instantiate<T>(createPos, Quat());
			auto throwCtrl = newObj->GetComponent<ThrowObjectCtrl>();

			if (throwCtrl) {
				throwCtrl->Throw(owner, direct, speed);
			}
		}

	};

}

//endbasecross