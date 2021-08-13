/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"
#include "PlayerWeightMgr.h"

namespace basecross {

	/// <summary>
	/// 一定回数踏んだら壊れるクッキー
	/// </summary>
	class CrackCookie : public Component
	{
		/// <summary>
		/// 耐久度
		/// </summary>
		float m_durability = 2.0f;

		float CalucDamage(const std::shared_ptr<PlayerWeightMgr>& weightMgr);
		void DestProcess();
		void Crack(const float& damage);

	public:

		CrackCookie(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override{}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
	};

}

//endbasecross