/*!
@file StageObject.cpp
@brief �X�e�[�W�ɔz�u����I�u�W�F�N�g����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"
#include "StageObject.h"

#include "LoadStageTriggerObject.h"

#include "LoadStageTrigger.h"

namespace basecross {

	void LoadStageTriggerObject::OnCreate() {
		auto trigger = AddComponent<LoadStageTrigger>();
		//trigger->SetNextMap(m_nextMap);

		//���̌���
		//auto draw = AddComponent<BcPNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross