/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"
#include "WallEvasionTactile.h"

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
		ex_weak_ptr<WallEvasionTactile> m_tactile;  //触覚

		vector<ex_weak_ptr<GameObject>> m_obstacleObjs;
		float m_range = 2.0f;
		float m_maxSpeed = 20.0f;

		//bool SortObstacleRange(const ObstacleRangePair& left, const ObstacleRangePair& right);
		//壁との距離を測定する。
		vector<ObstacleRangePair> CalucWallRangeSort();
		Vec3 CalucForce();

		//壁回避処理
		void EvasionUpdate(const std::shared_ptr<GameObject>& other);

	public:
		WallEvasion(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<WallEvasionTactile>& tactile	
		)
			:Component(objPtr),m_tactile(tactile)
		{}
		
		void OnCreate() override;
		void OnUpdate() override;


		//アクセッサ----------------------------------------------------
		void AddObstacleObjs(const std::shared_ptr<GameObject>& obj) {
			m_obstacleObjs.push_back(obj);
		}

		void SetTactile(const std::shared_ptr<WallEvasionTactile>& tactile) {
			m_tactile = tactile;
		}

		void SetRange(const float& range) {
			m_range = range;
		}
		float GetRange() const {
			return m_range;
		}

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

	};

}

//endbasecross