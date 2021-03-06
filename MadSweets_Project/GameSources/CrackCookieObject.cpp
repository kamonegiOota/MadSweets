
/*!
@file CrackCookieObject.cpp
@brief CrackCookieObject?N???X????
?S???F?ێR?T??
*/

#include "stdafx.h"
#include "Project.h"

#include "CrackCookieObject.h"
#include "CrackCookie.h"
#include "PNTPointDraw.h"

namespace basecross {

	void CrackCookieObject::OnCreate() {
		StageObject::OnCreate();

		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		draw->SetTextureResource(L"Cokie_Tx");
		transform->SetScale(Vec3(1.0f,0.1f,1.0f));

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
		
		AddComponent<CrackCookie>();
	}

}

//endbasecross