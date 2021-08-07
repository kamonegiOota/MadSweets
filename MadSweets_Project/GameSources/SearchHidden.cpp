/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
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
			if (toVec.length() < nearRange) { //�߂��ɍ���������ɓ����B
				reTargets.push_back(hide->GetGameObject());
			}
		}

		return reTargets;
	}

	std::shared_ptr<GameObject> SearchHidden::SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange,
		const std::shared_ptr<GameObject>& excluteObj
	) 
	{
		auto nearHides = SearchNearHiddenObjects(self ,nearRange);  //�߂��̉B���I�u�W�F�N�g�̌���
		maru::MyUtility::RemoveVec(nearHides, excluteObj);  //��x�m�F�����I�u�W�F�N�g��r��

		DebugObject::sm_wss << endl << L"Hide::" + to_wstring(nearHides.size()) << endl;

		if (nearHides.size() == 0) {  //�Ώۂ�����������null��Ԃ��B
			return nullptr;
		}

		auto obj = maru::MyRandom::RandomArray(nearHides);  //�z��̒����烉���_���Ɏ擾
		return obj;
	}

}

//endbasecross