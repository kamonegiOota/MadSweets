
/*!
@file MTestBox.cpp
@brief MTestBoxクラス実体
担当：丸山裕喜
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