/*!
@file ChaseAstarMove.h
@brief ChaseAstarMove
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

		int m_numLostChase = 1;  //LostMoveをする回数
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //ターゲットの場所に近いと判断される長さ。
		float m_lostSeekTime = 3.0f;     //ターゲットとの間に障害物がある場合。

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

		/// <summary>
		/// ターゲットに向かって障害物があるか判断する。
		/// </summary>
		/// <param name="target">ターゲット</param>
		/// <returns>障害物があるならtrue</returns>
		bool IsRayObstacle(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ターゲットに向かって障害物があるか判断する。
		/// </summary>
		/// <param name="targetPosition">ターゲットのポジション</param>
		/// <param name="excluteObjs">障害物から省く対象</param>
		/// <returns>障害物があるならtrue</returns>
		bool IsRayObstacle(const Vec3& targetPosition, vector<shared_ptr<GameObject>>& excluteObjs = vector<shared_ptr<GameObject>>());

		void Rotation(const Vec3& moveVec);

		/// <summary>
		/// ルートの検索
		/// </summary>
		/// <param name="target">検索する対象</param>
		void CalcuRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// 二回目以降にターゲットの場所を調べる処理
		/// </summary>
		/// <param name="target">ターゲット</param>
		void CalcuNextRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// 移動の力を計算して返す
		/// </summary>
		/// <param name="target">追いかける対象</param>
		/// <returns>移動の力</returns>
		Vec3 CalcuMoveForce(const std::shared_ptr<GameObject>& target);

		//ターゲットロストまでのカウントをスタート
		void LostTimerStart();
		//ターゲットロスト状態の解除
		void LostTimerCancel();

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