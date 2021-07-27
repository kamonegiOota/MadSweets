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

	struct EyeTargetParam {
		std::shared_ptr<GameObject> target;
		mutable bool isFind;  //見つけた状態かどうかを返す

		EyeTargetParam(const std::shared_ptr<GameObject>& target):
			target(target),
			isFind(false)
		{}
	};

	struct EyeSearchRangeParam {
		float lenght; //索敵範囲(同心円状)
		float height; //索敵範囲(高さ)
		float rad;    //索敵範囲(角度)

		EyeSearchRangeParam()
			:EyeSearchRangeParam(20.0f,3.0f,XMConvertToRadians(30.0f))
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
		std::vector<EyeTargetParam> m_targetParams;

		EyeSearchRangeParam m_param;

		/// <summary>
		/// ターゲットが自分を中心に球体状の範囲内にいるかどうか判断
		/// </summary>
		void LengthCheck();
		/// <summary>
		/// ターゲットが自分の索敵範囲内の「高さ」にいるかどうかを判断
		/// </summary>
		/// <param name="target">索敵ターゲット</param>
		void HeightCheck(const EyeTargetParam& tagetParam);
		/// <summary>
		/// ターゲットが自分の索敵範囲内の角度にいるか判断
		/// </summary>
		/// <param name="target">索敵ターゲット</param>
		void RadCheck(const EyeTargetParam& targetParam);
		/// <summary>
		/// Rayを飛ばしたときのチェック
		/// </summary>
		/// <param name="targetParam">索敵ターゲット</param>
		void RayCheck(const EyeTargetParam& targetParam);

		/// <summary>
		/// ターゲットが索敵範囲内にいるときに呼び出される関数
		/// </summary>
		void Hit(const EyeTargetParam& targetParam);

	public:
		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr);

		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr,
			const EyeSearchRangeParam& param);

		void OnCreate() override {}
		void OnUpdate() override;

		//アクセッサ-------------------------------------------------------------------------
		void AddTarget(const std::shared_ptr<GameObject>& obj) {
			m_targetParams.push_back(EyeTargetParam(obj));
		}

		void SetParam(const EyeSearchRangeParam& param) {
			m_param = param;
		}
		EyeSearchRangeParam GetParam() const {
			return m_param;
		}

		//見つけている状態かどうかを判断する
		bool IsLookTarget(const std::shared_ptr<GameObject>& target) {
			for (auto param : m_targetParams) {
				if (target == param.target) {  //同じ種類だったら
					return param.isFind;
				}
			}

			return false;
		}

	};

}

//endbasecross