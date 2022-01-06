
/*!
@file SoundCookieObject.cpp
@brief SoundCookieObjectクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "SoundCookieObject.h"
#include "SoundCookie.h"
#include "PNTPointDraw.h"

namespace basecross {

	void SoundCookieObject::OnCreate() {
		StageObject::OnCreate();
		
		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		draw->SetTextureResource(L"Cokie_Tx");
		transform->SetScale(Vec3(1.0f, 0.1f, 1.0f));

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		AddComponent<SoundCookie>();

		//テスト的に薄くする
		//transform->SetScale(Vec3(1.0f, 0.3f, 1.0f));
	}

}

//endbasecross