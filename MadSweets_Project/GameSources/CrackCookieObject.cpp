
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "CrackCookieObject.h"
#include "CrackCookie.h"
#include "PNTPointDraw.h"

namespace basecross {

	void CrackCookieObject::OnCreate() {
		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		auto col = AddComponent<CollisionObb>();
		
		AddComponent<CrackCookie>();
	}

}

//endbasecross