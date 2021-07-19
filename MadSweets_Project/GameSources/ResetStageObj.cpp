/*!
@file FixedBox.cpp
@brief FixedBoxŽÀ‘Ì
’S“–FŠÛŽR—TŠì
*/

#include "stdafx.h"
#include "Project.h"
#include "ResetStageObj.h"

namespace basecross {

	void ResetStageObj::OnCreate()
	{
		SetSRP();
	}


	void ResetStageObj::ResetAll()
	{
		ResetUpdate();
		ResetSRP();
	}

	void ResetStageObj::ResetUpdate()
	{
		auto obj = GetGameObject();

		obj->SetUpdateActive(true);
		obj->SetDrawActive(true);
	}

	void ResetStageObj::ResetSRP()
	{
		auto objTrans = GetGameObject()->GetComponent<Transform>();

		objTrans->SetScale(m_scale);
		//objTrans->SetRotation(m_rotation);
		objTrans->SetQuaternion(m_quat);
		objTrans->SetPosition(m_position);
	}

}

//endbasecross