
/*!
@file MTestBox.cpp
@brief MTestBox�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "MTestBox.h"

namespace basecross {

	void MTestBox::OnCreate() {
		auto draw = AddComponent<BcPNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");

		auto col = AddComponent<CollisionObb>();
		//col->SetAfterCollision(AfterCollision::None);
	}

}

//endbasecross