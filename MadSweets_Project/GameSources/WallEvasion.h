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
		//vector<ex_weak_ptr<WallEvasionTactile>> m_tactiles;  //触覚

		vector<ex_weak_ptr<GameObject>> m_obstacleObjs;
		float m_range = 2.0f;
		float m_maxSpeed = 30.0f;

		//bool SortObstacleRange(const ObstacleRangePair& left, const ObstacleRangePair& right);
		//壁との距離を測定する。
		vector<ObstacleRangePair> CalucWallRangeSort();
		Vec3 CalucForce(const std::shared_ptr<GameObject>& tactile);

		//壁回避処理
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

		//触覚のセット
		void SetTactile(const std::shared_ptr<TactileCtrl>& tactile) {
			tactile->AddExcuteAction([this](const std::shared_ptr<TactileCtrl>& tactile,const std::shared_ptr<GameObject>& other) {
				EvasionUpdate(tactile,other);
			});
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