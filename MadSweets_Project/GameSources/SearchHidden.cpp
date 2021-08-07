/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchHidden.h"
#include "HiddenComponent.h"
#include "MyUtility.h"
#include "Mathf.h"
#include "MyRandom.h"

#include "DebugObject.h"

namespace basecross {

	vector<std::shared_ptr<GameObject>> SearchHidden::SearchNearHiddenObjects(const std::shared_ptr<GameObject>& self, const float& nearRange) {
		auto hides = maru::MyUtility::GetComponents<HiddenComponent>();
		
		vector <std::shared_ptr<GameObject>> reTargets;
		for (auto& hide : hides) {
			auto toVec = maru::MyUtility::CalucToTargetVec(self, hide->GetGameObject());
			if (toVec.length() < nearRange) { //近くに合ったら候補に入れる。
				reTargets.push_back(hide->GetGameObject());
			}
		}

		return reTargets;
	}

	std::shared_ptr<GameObject> SearchHidden::SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange,
		const std::shared_ptr<GameObject>& excluteObj
	) 
	{
		auto nearHides = SearchNearHiddenObjects(self ,nearRange);  //近くの隠れるオブジェクトの検索
		maru::MyUtility::RemoveVec(nearHides, excluteObj);  //一度確認したオブジェクトを排除

		DebugObject::sm_wss << endl << L"Hide::" + to_wstring(nearHides.size()) << endl;

		if (nearHides.size() == 0) {  //対象が無かったらnullを返す。
			return nullptr;
		}

		auto obj = maru::MyRandom::RandomArray(nearHides);  //配列の中からランダムに取得
		return obj;
	}

}

//endbasecross