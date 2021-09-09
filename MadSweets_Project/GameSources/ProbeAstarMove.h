/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"

#include "BaseUseVelocity.h"
#include "AstarCtrl.h"

namespace basecross {

	//ターゲット追従中にAstarを利用して移動したい時のコンポーネント
	class ProbeAstarMove : public Component , public BaseUseVelocity
	{
		bool m_isProbeEnd = false;

		int m_numLostChase = 5;  //LostMoveをする回数
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //ターゲットの場所に近いと判断される長さ

		ex_weak_ptr<GameObject> m_target;
		Vec3 m_targetPosition = Vec3(0.0f);

		//NumLostChaseElapsedのリセット
		void ResetNumLostChaseElapsed();

		bool IsRouteEnd();

		void Rotation(const Vec3& moveVec);
		void ChangeTargetChase();

		void CalucRoute(const std::shared_ptr<GameObject>& target);
		void CalucNextRoute(const std::shared_ptr<GameObject>& target);

	public:

		ProbeAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override {}

		//Astarを利用した移動
		void Move();

		/// <summary>
		/// ターゲットが視界から外れた時の処理
		/// </summary>
		/// <param name="target">追従中のターゲット</param>
		void LostTarget(const std::shared_ptr<GameObject>& target);
		//次のルートを検索する。
		void NextRoute();

		//アクセッサ-----------------------------------------------------------

		/// <summary>
		/// 探索が終了しているかどうかを判断
		/// </summary>
		/// <returns>終了していたらtrue</returns>
		bool IsProbeEnd() const {
		 	return m_isProbeEnd;
		}

		void SetNumLostCheck(const int& num) {
			m_numLostChase = num;
		}
		int GetNumLostCheck() const {
			return m_numLostChase;
		}

		/// <summary>
		/// 目的の場所に近いと判断される距離のセット
		/// </summary>
		/// <param name="range">目的の場所に近いと判断される距離</param>
		void SetTargetNearRange(const float& range) {
			m_targetNearRange = range;
		}
		float GetTargetNearRange() const {
			return m_targetNearRange;
		}
	};

}

//endbasecross