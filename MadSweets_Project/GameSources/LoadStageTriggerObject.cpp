/*!
@file StageObject.cpp
@brief ステージに配置するオブジェクト実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"
#include "StageObject.h"

#include "LoadStageTriggerObject.h"

#include "LoadStageTrigger.h"

namespace basecross {

	void LoadStageTriggerObject::OnCreate() {
		StageObject::OnCreate();

		auto trigger = AddComponent<LoadStageTrigger>();
		trigger->SetNextMap(m_nextMap);

		//仮の見た目
		//auto draw = AddComponent<BcPNTStaticDraw>();
		//draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross