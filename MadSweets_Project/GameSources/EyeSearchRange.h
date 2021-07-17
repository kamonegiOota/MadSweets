/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "DelegateSystem.h"

namespace basecross {

	struct EyeSearchRangeParam {
		float lenght; //索敵範囲(同心円状)
		float height; //索敵範囲(高さ)
		float rad;    //索敵範囲(角度)

		EyeSearchRangeParam()
			:EyeSearchRangeParam(5.0f,3.0f,XMConvertToRadians(30.0f))
		{}

		EyeSearchRangeParam(const float& lenght,
			const float& height,
			const float& rad
		):
			lenght(lenght),
			height(height),
			rad(rad)
		{}
	};

	/// <summary>
	/// 視界範囲をコントロールするコンポーネント
	/// </summary>
	class EyeSearchRange : public Component
	{
		//範囲に入っているかの対象になるオブジェクト
		std::vector<std::shared_ptr<GameObject>> m_targets;

		EyeSearchRangeParam m_param;

		/// <summary>
		/// ターゲットが自分を中心に球体状の範囲内にいるかどうか判断
		/// </summary>
		void LengthCheck();
		/// <summary>
		/// ターゲットが自分の索敵範囲内の「高さ」にいるかどうかを判断
		/// </summary>
		/// <param name="target">索敵ターゲット</param>
		void HeightCheck(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ターゲットが自分の索敵範囲内の角度にいるか判断
		/// </summary>
		/// <param name="target">索敵ターゲット</param>
		void RadCheck(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ターゲットが索敵範囲内にいるときに呼び出される関数
		/// </summary>
		void Hit(const std::shared_ptr<GameObject>& target);

	public:
		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr);

		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr,
			const EyeSearchRangeParam& param);

		void OnCreate() override {}
		void OnUpdate() override;

		//アクセッサ-------------------------------------------------------------------------
		void AddTarget(const std::shared_ptr<GameObject>& obj) {
			m_targets.push_back(obj);
		}

		void SetParam(const EyeSearchRangeParam& param) {
			m_param = param;
		}
		EyeSearchRangeParam GetParam() const {
			return m_param;
		}

	};

}

//endbasecross