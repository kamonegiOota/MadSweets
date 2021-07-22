/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "EyeSearchRange.h"
#include "MyUtility.h"
#include "DebugObject.h"

#include "I_Chase.h"
#include "MyUtility.h"

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

	void EyeSearchRange::LengthCheck() {
		for (auto& param : m_targetParams) {
			auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), param.target);
			if (toVec.length() <= m_param.lenght) {
				HeightCheck(param);  //高さチェック
			}
			else {
				param.isFind = false;
			}
		}
	}

	void EyeSearchRange::HeightCheck(const EyeTargetParam& targetParam) {
		auto selfPos = transform->GetPosition();
		auto targetPos = targetParam.target->GetComponent<Transform>()->GetPosition();

		auto subHeight = targetPos.y - selfPos.y;  //高さの差を求める。
		if (std::abs(subHeight) <= m_param.height) {  //高さが小さかったら。
			RadCheck(targetParam);  //角度チェック
		}
		else {
			targetParam.isFind = false;
		}
	}

	void EyeSearchRange::RadCheck(const EyeTargetParam& targetParam) {
		auto forward = transform->GetForword();
		forward.y = 0.0f;
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), targetParam.target);
		toVec.y = 0.0f;

		auto newDot = dot(forward.GetNormalized(), toVec.GetNormalized());
		auto newRad = acosf(newDot);
		if (newRad <= m_param.rad) {  //索敵範囲に入っていたら。
			RayCheck(targetParam);
		}
		else {
			targetParam.isFind = false;
		}
	}

	void EyeSearchRange::RayCheck(const EyeTargetParam& targetParam) {
		const auto& target = targetParam.target;
	
		//障害物にヒットしなかったら
		if (maru::MyUtility::IsRayObstacle(GetGameObject(),target) == false) {
			Hit(targetParam);
		}
		else {
			targetParam.isFind = false;
		}
	}

	void EyeSearchRange::Hit(const EyeTargetParam& targetParam) {
		targetParam.isFind = true;

		auto chase = GetGameObject()->GetComponent<I_Chase>(false);
		if (chase) {
			chase->ChangeChaseState(targetParam.target);
			//DebugObject::m_wss << L"Chase,";
			return;
		}
	}

	void EyeSearchRange::OnUpdate() {
		LengthCheck();
	}

}

//endbasecross