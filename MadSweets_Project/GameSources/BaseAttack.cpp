/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "BaseAttack.h"
#include "MyUtility.h"

namespace basecross {

	bool BaseAttack::IsAttackRange(const bool isObstacleChek) {
		if (m_target == nullptr) {
			return false;
		}

		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), m_target);
		auto range = toVec.length();
		
		//障害物チェックをする　且つ　障害物があったら
		if (isObstacleChek && maru::MyUtility::IsRayObstacle(GetGameObject(), m_target)) {
			return false;  //範囲外
		}
		else {
			//障害物が無かったら
			return range <= m_param.range ? true : false;   //指定の範囲内にいたらtrue
		}

	}

}

//endbasecross