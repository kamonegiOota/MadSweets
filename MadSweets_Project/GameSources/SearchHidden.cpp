/*!
@file PlowlingMove.cpp
@brief PlowlingMove‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchHidden.h"
#include "HiddenComponent.h"
#include "MyUtility.h"
#include "Mathf.h"
#include "MyRandom.h"

namespace basecross {

	vector<std::shared_ptr<GameObject>> SearchHidden::SearchNearHiddenObjects(const std::shared_ptr<GameObject>& self, const float& nearRange) {
		auto hides = maru::MyUtility::GetComponents<HiddenComponent>();
		
		vector <std::shared_ptr<GameObject>> reTargets;
		for (auto& hide : hides) {
			auto toVec = maru::MyUtility::CalucToTargetVec(self, hide->GetGameObject());
			if (toVec.length() < nearRange) { //‹ß‚­‚É‡‚Á‚½‚çŒó•â‚É“ü‚ê‚éB
				reTargets.push_back(hide->GetGameObject());
			}
		}

		return reTargets;
	}

	std::shared_ptr<GameObject> SearchHidden::SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange) {
		auto nearHides = SearchNearHiddenObjects(self ,nearRange);

		auto obj = maru::MyRandom::RandomArray(nearHides);
		return obj;
	}

}

//endbasecross