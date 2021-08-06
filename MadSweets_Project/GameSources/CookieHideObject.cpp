
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "CookieHideObject.h"
#include "PNTPointDraw.h"
#include "HiddenComponent.h"

namespace basecross {

	void CookieHideObject::OnCreate() {
		StageObject::OnCreate();

		AddComponent<HiddenComponent>(transform->GetPosition(), transform->GetForword());
		AddComponent<PNTPointDraw>()->SetMeshResource(L"DEFAULT_CUBE");
		AddComponent<CollisionObb>()->SetFixed(true);
	}

	

}

//endbasecross