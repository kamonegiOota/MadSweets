/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"
#include "TactileCtrl.h"

namespace basecross {

	struct ObstacleRangePair
	{
		ex_weak_ptr<GameObject> object;
		float range;

		ObstacleRangePair()
			:ObstacleRangePair(nullptr, 0.0f)
		{}

		ObstacleRangePair(const std::shared_ptr<GameObject>& objPtr, const float& range)
			:object(objPtr), range(range)
		{}
	};

	class WallEvasion : public Component
	{
		//障害物の対象
		vector<ex_weak_ptr<GameObject>> m_obstacleObjs;
		float m_maxSpeed = 30.0f;

		/// <summary>
		/// 壁との距離を測定して、小さい順に並べて配列を返す
		/// </summary>
		/// <returns>壁との距離を測定した配列</returns>
		vector<ObstacleRangePair> CalucWallRangeSort();
		/// <summary>
		/// 加える力を計算する。
		/// </summary>
		/// <param name="tactile">触覚オブジェクト</param>
		/// <returns>計算した力</returns>
		Vec3 CalucForce(const std::shared_ptr<GameObject>& tactile);

		/// <summary>
		/// 壁回避処理
		/// </summary>
		/// <param name="tactile">触覚オブジェクト</param>
		/// <param name="other">接触したオブジェクト</param>
		void EvasionUpdate(const std::shared_ptr<TactileCtrl>& tactile, const std::shared_ptr<GameObject>& other);

	public:
		WallEvasion(const std::shared_ptr<GameObject>& objPtr
		)
			:Component(objPtr)
		{}
		
		void OnCreate() override {}
		void OnUpdate() override {}


		//アクセッサ----------------------------------------------------

		void AddObstacleObjs(const std::shared_ptr<GameObject>& obj) {
			m_obstacleObjs.push_back(obj);
		}

		/// <summary>
		/// 触覚のセット
		/// </summary>
		/// <param name="tactile">触覚のオブジェクト</param>
		void SetTactile(const std::shared_ptr<TactileCtrl>& tactile);

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

	};

}

//endbasecross