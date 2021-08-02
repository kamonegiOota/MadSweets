/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"

namespace basecross {

	/// <summary>
	/// 固定のルートを徘徊するコンポーネント
	/// </summary>
	class PlowlingMove : public Component
	{
		//ex_weak_ptr<AstarCtrl> m_astar;

		/// <summary>
		/// 徘徊するポジション
		/// </summary>
		std::vector<Vec3> m_positions;

		int m_index;  //現在向かっているポジションのインデックス
		int m_addIndexDirect;  //インデックスが増える方向

		float m_maxSpeed = 2.0f;  //最大スピードを設定する、plowlingMove時の
		float m_nearRange = 3.5f; //近くにいるかどうかの判断をする。

		/// <summary>
		/// 次のポジションまでのベクトルを計算して返す。
		/// </summary>
		/// <returns>計算したベクトルを返す。</returns>
		Vec3 CalucMoveVec();
		/// <summary>
		/// 実際の移動処理
		/// </summary>
		void Move();
		void Rotation(const Vec3& moveVec);
		/// <summary>
		/// 目的地に限りなく近い場所にいるならtrue
		/// </summary>
		/// <param name="pos">現在のポジション</param>
		/// <returns>目的地に近い場合true</returns>
		bool IsNearArrival(const Vec3& pos);
		/// <summary>
		/// 次の目的地のインデックスに切り替える処理
		/// </summary>
		void NextIndex();

		//void RandomAstarMove();

	public:

		PlowlingMove(const std::shared_ptr<GameObject>& objPtr);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions
		);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions,
			const float& speed,
			const float& nearRange
		);
		
		void OnCreate() {}
		void OnStart();
		void OnUpdate();
		void OnDraw(){}
		
		//アクセッサ----------------------------------------------
		void SetPositions(const std::vector<Vec3>& positions){
			m_positions = positions;
		}

		void AddPosition(const Vec3& position) {
			m_positions.push_back(position);
		}

		float GetMaxSpeed() const {
			return m_maxSpeed;
		}
		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}

		float GetNearRange() const {
			return m_nearRange;
		}
		void SetNearRange(const float& nearRange) {
			m_nearRange = nearRange;
		}

		/// <summary>
		/// 現在向かっているポジションを返す
		/// </summary>
		/// <returns>現在向かっているポジション</returns>
		Vec3 GetNowTargetPosition() const {
			return m_positions[m_index];
		}
	};

}

//endbasecross