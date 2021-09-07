
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "NumbersObject.h"
#include "NumbersCtrl.h"
#include "BillBoard.h"

namespace basecross {

	void NumbersObject::OnCreate() {
		AddComponent<NumbersCtrl>();

		AddComponent<BillBoard>();
	}

}

//endbasecross