/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EyeSearchRange.h"
#include "MyUtility.h"
#include "DebugObject.h"

#include "I_Chase.h"
#include "I_Escape.h"
#include "BaseAttack.h"
#include "MyUtility.h"

#include "ThrowObjectCtrl.h"
#include "HiddenComponent.h"

namespace basecross {

	EyeSearchRange::EyeSearchRange(const std::shared_ptr<GameObject>& objPtr)
		:EyeSearchRange(objPtr,EyeSearchRangeParam())
	{}

	EyeSearchRange::EyeSearchRange(const std::shared_ptr<GameObject>& objPtr,
		const EyeSearchRangeParam& param
	):
		Component(objPtr),
		m_param(param)
	{}


	bool EyeSearchRange::IsRange(const std::shared_ptr<GameObject>& target) {
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), target);
		//�����`�F�b�N
		return toVec.length() <= m_param.lenght ? true : false;
	}

	bool EyeSearchRange::IsHeight(const std::shared_ptr<GameObject>& target) {
		auto selfPos = transform->GetPosition();
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		auto subHeight = targetPos.y - selfPos.y;  //�����̍������߂�B
		//������������������B
		return std::abs(subHeight) <= m_param.height ? true : false;
	}

	bool EyeSearchRange::IsRad(const std::shared_ptr<GameObject>& target) {
		auto forward = transform->GetForword();
		forward.y = 0.0f;
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), target);
		toVec.y = 0.0f;

		auto newDot = dot(forward.GetNormalized(), toVec.GetNormalized());
		auto newRad = acosf(newDot);
		//���G�͈͂ɓ����Ă�����B
		return newRad <= m_param.rad ? true : false;
	}

	bool EyeSearchRange::IsRay(const std::shared_ptr<GameObject>& target){
		//�ΏۊO�ƂȂ�I�u�W�F�N�g�̎w��B
		vector<shared_ptr<GameObject>> excluteObjs;
		maru::MyUtility::AddComponents<ThrowObjectCtrl>(excluteObjs);
		//maru::MyUtility::AddComponents<HiddenComponent>(excluteObjs);

		//��Q���Ƀq�b�g���Ȃ�������
		return !maru::MyUtility::IsRayObstacle(GetGameObject(), target, excluteObjs) ? true : false;
	}


	void EyeSearchRange::Hit(const EyeTargetParam& targetParam) {
		targetParam.isFind = true;
		auto obj = GetGameObject();
		
		auto attack = obj->GetComponent<BaseAttack>(false);
		if (attack) {
			attack->Attack(targetParam.target);
		}

		auto chase = obj->GetComponent<I_Chase>(false);
		if (chase) {
			chase->ChangeChaseState(targetParam.target);
			return;
		}

		auto escape = obj->GetComponent<I_Escape>(false);
		if (escape) {
			escape->ChangeEscapeState(targetParam.target);
			return;
		}
	}

	void EyeSearchRange::OnUpdate() {
		for (auto& param : m_targetParams) {
			if (IsInEyeRange(param.target)) {  //�^�[�Q�b�g�����E�ɓ����Ă�����B
				Hit(param);
			}
			else {
				param.isFind = false;
			}
		}
	}

	bool EyeSearchRange::IsInEyeRange(std::shared_ptr<GameObject>& target) {
		//�S�Ă̏�����true�Ȃ王�E���ɑΏۂ�����B
		if (IsRange(target) && IsHeight(target) && IsRad(target) && IsRay(target)) {
			return true;
		}
		else {
			return false;
		}
	}

}

//endbasecross