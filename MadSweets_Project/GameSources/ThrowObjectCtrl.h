/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// 投げられたオブジェクトのコントロール
	/// </summary>
	class ThrowObjectCtrl : public Component
	{
		std::shared_ptr<GameObject> m_owner;
		float m_attackPower;

		void Rotation(const Vec3& direct);

	public:
		ThrowObjectCtrl(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr), m_attackPower(2.0f)
		{}

		void OnCreate() override{}
		void OnStart() override{}
		void OnUpdate() override{}

		/// <summary>
		/// 投げるときの関数
		/// </summary>
		/// <param name="owner">投げたオブジェクト</param>
		/// <param name="direct">投げる方向</param>
		/// <param name="speed">飛んでいくスピード</param>
		void Throw(const std::shared_ptr<GameObject>& owner, const Vec3& direct, const float& speed);

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;


		//アクセッサ------------------------------------------------------------

		void SetOwner(const std::shared_ptr<GameObject>& owner) {
			m_owner = owner;
		}
	};

}

//endbasecross