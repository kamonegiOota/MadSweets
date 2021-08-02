
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
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