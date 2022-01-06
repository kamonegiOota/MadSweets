/*!
@file EarBase.cpp
@brief EarBase‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "EarBase.h"

namespace basecross {

	void EarBase::Listen(const std::shared_ptr<GameObject>& target) {
		auto targetPos = target->GetComponent<Transform>()->GetPosition();

		Listen(targetPos);
	}

}

//endbasecross