/*!
@file StageObject.cpp
@brief ステージに配置するオブジェクト実体 
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"
#include "StageObject.h"

namespace basecross {

	void StageObject::OnCreate()
	{
		auto transform = GetComponent<Transform>();

		transform->SetScale(m_scale);
		transform->SetRotation(m_rotation);
		transform->SetPosition(m_position);

		AddComponent<ResetStageObj>()->SetSRP();
	}

}

//endbasecross