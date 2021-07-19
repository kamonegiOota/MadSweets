/*!
@file StageObject.cpp
@brief �X�e�[�W�ɔz�u����I�u�W�F�N�g���� 
�S���F�ێR�T��
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