
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "Velocity.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	void ThrowHandyObject::OnCreate() {
		//将来的には見た目のみ消す
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");

		auto col = AddComponent<CollisionSphere>();
		col->SetAfterCollision(AfterCollision::None);

		AddComponent<Velocity>();
		AddComponent<ThrowObjectCtrl>();
	}

}

//endbasecross