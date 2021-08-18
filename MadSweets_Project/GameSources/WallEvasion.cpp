/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
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

		std::sort(rangePairs.begin(), rangePairs.end(), SortObstacleRange);

		return rangePairs;
	}

	Vec3 WallEvasion::CalucForce() {
		Vec3 returnVec(0.0f);

		auto obstacleRangePairs = CalucWallRangeSort();
		auto startPos = transform->GetPosition();
		for (auto& pair : obstacleRangePairs) {
			auto& obj = pair.object;
			auto col = obj->GetComponent<Collision>(false);
			if (!col) { //ƒRƒŠƒWƒ‡ƒ“‚ª–³‚©‚Á‚½‚çˆ—‚ð‚µ‚È‚¢
				continue;
			}

			RayHitData data;
			auto toVec = obj->GetComponent<Transform>()->GetPosition() - startPos;
			toVec.y = 0.0f;
			if (col->IsRayHit(startPos, toVec.GetNormalized(), data)) {
				if (data.length <= m_range) {
					//float t;
					//Vec3 d;
					//auto Matrix = GetGameObject()->GetComponent<Transform>()->GetWorldMatrix();
					//auto velocity = GetGameObject()->GetComponent<Velocity>()->GetVelocity();
					//returnVec += d - data.point;
					returnVec += startPos - data.point;
				}
			}
		}

		returnVec.y = 0;
		return returnVec;
	}

	void WallEvasion::EvasionUpdate(const std::shared_ptr<GameObject>& other) {

		//DebugObject::sm_wss << L"Hit";
		auto delta = App::GetApp()->GetElapsedTime();
		auto newForce = CalucForce();

		auto velocityComp = GetGameObject()->GetComponent<Velocity>();
		if (velocityComp) {
			auto velocity = velocityComp->GetVelocity();
			auto vec = newForce;
			//auto vec = newForce - velocity;
			//auto vec = velocity - newForce;
			//auto length = vec.length();
			
			auto power = m_maxSpeed - vec.length();
			//power = maru::Mathf::Max(power, m_maxSpeed);

			auto force = vec.normalize() * power * delta;

			velocityComp->AddForce(force);
		}
	}

	void WallEvasion::OnCreate() {
		if (m_tactile) {
			m_tactile->AddExcuteAction([this](const std::shared_ptr<GameObject>& other) {
				EvasionUpdate(other);
			});
		}
	}

	void WallEvasion::OnUpdate() {
		//EvasionUpdate();
	}

}

//endbasecross