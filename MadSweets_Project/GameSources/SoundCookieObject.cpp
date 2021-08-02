
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "SoundCookieObject.h"
#include "SoundCookie.h"
#include "PNTPointDraw.h"

namespace basecross {

	void SoundCookieObject::OnCreate() {
		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
		//col->SetFixed(true);

		AddComponent<SoundCookie>();

		//テスト的に薄くする
		transform->SetScale(Vec3(1.0f, 0.3f, 1.0f));
	}

}

//endbasecross