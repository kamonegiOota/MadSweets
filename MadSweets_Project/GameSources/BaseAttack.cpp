/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
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
		
		//��Q���`�F�b�N������@���@��Q������������
		if (isObstacleChek && maru::MyUtility::IsRayObstacle(GetGameObject(), m_target)) {
			return false;  //�͈͊O
		}
		else {
			//��Q��������������
			return range <= m_param.range ? true : false;   //�w��͈͓̔��ɂ�����true
		}

	}

}

//endbasecross