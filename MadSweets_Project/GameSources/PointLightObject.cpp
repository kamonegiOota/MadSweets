/*!
@file PointLightObject.cpp
@brief PointLightObjectクラス実体
担当：丸山裕喜
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