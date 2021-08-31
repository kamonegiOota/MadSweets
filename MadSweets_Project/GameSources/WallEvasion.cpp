/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "WallEvasion.h"
#include "MyUtility.h"
#include "Velocity.h"
#include "UtilVelocity.h"
#include "Mathf.h"

namespace basecross {

	bool SortObstacleRange(const ObstacleRangePair& left, const ObstacleRangePair& right) {
		return left.range <= right.range ? true : false;
	}

	std::vector<ObstacleRangePair> WallEvasion::CalucWallRangeSort() {
		vector<ObstacleRangePair> rangePairs;

		for (auto& obj : m_obstacleObjs) {
			auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), obj.GetShard());
			rangePairs.push_back(ObstacleRangePair(obj.GetShard(), toVec.length()));
		}

		//バグが起きたため応急処置
		//std::sort(rangePairs.begin(), rangePairs.end(), SortObstacleRange);
		ObstacleRangePair minRangePair;
		float minRange = 100000.0f;
		for (auto& pair : rangePairs) {
			if (pair.range < minRange) {
				minRangePair = pair;
			}
		}

		vector<ObstacleRangePair> reVector;
		reVector.push_back(minRangePair);
		return reVector;
		//return rangePairs;
	}

	Vec3 WallEvasion::CalucForce(const std::shared_ptr<GameObject>& tactile) {
		Vec3 returnVec(0.0f);

		if (m_obstacleObjs.size() == 0.0f) {
			return returnVec;
		}

		auto obstacleRangePairs = CalucWallRangeSort();
		auto startPos = transform->GetPosition();
		for (auto& pair : obstacleRangePairs) {
			auto& obj = pair.object;
			auto col = obj->GetComponent<Collision>(false);
			if (!col) { //コリジョンが無かったら処理をしない
				continue;
			}

			RayHitData data;
			auto tactileTrans = tactile->GetComponent<Transform>();
			
			if (col->IsRayHit(startPos, tactileTrans->GetForword(), data)) {
				returnVec += startPos - data.point;
				break;
			}
		}

		returnVec.y = 0;
		return returnVec;
	}

	void WallEvasion::EvasionUpdate(const std::shared_ptr<TactileCtrl>& tactile, const std::shared_ptr<GameObject>& other) {
		if (GetUpdateActive() == false) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		auto newForce = CalucForce(tactile->GetGameObject());

		auto velocityComp = GetGameObject()->GetComponent<Velocity>();
		if (velocityComp) {
			auto velocity = velocityComp->GetVelocity();
			
			auto power = m_maxSpeed - newForce.length();
			auto force = newForce.normalize() * power * delta;

			velocityComp->AddForce(force);
		}
	}

}

//endbasecross