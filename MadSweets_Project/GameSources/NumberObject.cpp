
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "Number.h"
#include "NumberObject.h"

namespace basecross {

	void NumberObject::OnCreate() {
		AddComponent<Number>(0);
	}

}

//endbasecross