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
	class ChaseAstarMove : public Component , public BaseUseVelocity
	{
		bool m_isProbeEnd = false;

		int m_numLostChase = 5;  //LostMoveをする回数
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //ターゲットの場所に近いと判断される長さ

		ex_weak_ptr<GameObject> m_target;   //ターゲットのポインタ
		Vec3 m_targetPosition = Vec3(0.0f); //現在向かっている場所

		/// <summary>
		/// NumLostChaseElapsedのリセット
		/// </summary>
		void ResetNumLostChaseElapsed();

		/// <summary>
		/// ターゲットの近くに来たらtrueを返す
		/// </summary>
		/// <returns>ターゲットの近くならtrue</returns>
		bool IsRouteEnd();

		void Rotation(const Vec3& moveVec);

		/// <summary>
		/// ルートの検索
		/// </summary>
		/// <param name="target">検索する対象</param>
		void CalucRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// 二回目以降にターゲットの場所を調べる処理
		/// </summary>
		/// <param name="target">ターゲット</param>
		void CalucNextRoute(const std::shared_ptr<GameObject>& target);

	public:

		ChaseAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override {}

		/// <summary>
		/// 移動処理
		/// </summary>
		void Move();

		/// <summary>
		/// ターゲットが視界から外れた時の処理
		/// </summary>
		/// <param name="target">追従中のターゲット</param>
		void LostTarget(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// 次のルートを検索する。
		/// </summary>
		void NextRoute();

		//アクセッサ-----------------------------------------------------------

		/// <summary>
		/// 探索が終了しているかどうかを判断
		/// </summary>
		/// <returns>終了していたらtrue</returns>
		bool IsProbeEnd() const {
		 	return m_isProbeEnd;
		}

		/// <summary>
		/// ターゲットを見失ってから何回調べるかをセットする
		/// </summary>
		/// <param name="num">ターゲットを見失ってから何回調べるか</param>
		void SetNumLostCheck(const int& num) {
			m_numLostChase = num;
		}
		/// <summary>
		/// ターゲットを見失ってから何回調べるか
		/// </summary>
		/// <returns>ターゲットを見失ってから何回調べるか</returns>
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
		/// <summary>
		/// 目的の場所に近いと判断される距離
		/// </summary>
		/// <returns>目的の場所に近いと判断される距離</returns>
		float GetTargetNearRange() const {
			return m_targetNearRange;
		}
	};

}

//endbasecross