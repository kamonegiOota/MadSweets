/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "PointLightObject.h"
#include "EatenComponent.h"
#include "SoundHelper.h"

#include "PNTPointDraw.h"

namespace basecross {

	void PointLightObject::OnCreate() {
		StageObject::OnCreate();

		AddComponent<PointLight>()->SetPower(0.25f);
	}

}

//endbasecross