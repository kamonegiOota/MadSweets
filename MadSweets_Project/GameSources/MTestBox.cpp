
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "MTestBox.h"

namespace basecross {

	void MTestBox::OnCreate() {
		auto draw = AddComponent<BcPNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
	}

}

//endbasecross