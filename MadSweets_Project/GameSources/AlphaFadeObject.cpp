/*!
@file AlphaFadeObject.cpp
@brief AlphaFadeObject�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "AlphaFadeObject.h"
#include "AlphaFadeCtrl.h"

namespace basecross {

	void AlphaFadeObject::OnCreate() {
		AddComponent<AlphaFadeCtrl>();
	}

}

//endbasecross