
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
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