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
		for (auto target : m_targets) {
			auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), target);
			if (toVec.length() <= m_param.lenght) {
				HeightCheck(target);  //高さチェック
			}
		}
	}

	void EyeSearchRange::HeightCheck(const std::shared_ptr<GameObject>& target) {
		auto selfPos = transform->GetPosition();
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		auto subHeight = targetPos.y - selfPos.y;  //高さの差を求める。
		if (std::abs(subHeight) <= m_param.height) {  //高さが小さかったら。
			RadCheck(target);  //角度チェック
		}
	}

	void EyeSearchRange::RadCheck(const std::shared_ptr<GameObject>& target) {
		auto forward = transform->GetForword();
		forward.y = 0.0f;
		auto toVec = maru::MyUtility::CalucToTargetVec(GetGameObject(), target);
		toVec.y = 0.0f;

		auto newDot = dot(forward.GetNormalized(), toVec.GetNormalized());
		auto newRad = acosf(newDot);
		if (newRad <= m_param.rad) {  //索敵範囲に入っていたら。
			Hit(target);
		}
	}

	void EyeSearchRange::Hit(const std::shared_ptr<GameObject>& target) {
		auto chase = GetGameObject()->GetComponent<I_Chase>(false);
		if (chase) {
			chase->ChangeChaseState(target);
			//DebugObject::m_wss << L"Chase,";
			return;
		}
	}

	void EyeSearchRange::OnUpdate() {
		LengthCheck();
	}

}

//endbasecross