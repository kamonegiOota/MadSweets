
/*!
@file ThrowObject.cpp
@brief ThrowObjectクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowObject.h"
#include "ThrowObjectCtrl.h"
#include "Velocity.h"

namespace basecross {

	void ThrowObject::OnCreate() {
		//将来的には見た目のみ消す
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<ThrowObjectCtrl>();
		AddComponent<Velocity>();
	}

}

//endbasecross