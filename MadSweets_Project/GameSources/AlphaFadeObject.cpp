/*!
@file AlphaFadeObject.cpp
@brief AlphaFadeObjectクラス実体
担当：丸山裕喜
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