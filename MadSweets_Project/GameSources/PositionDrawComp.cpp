/*!
@file PositionDrawComp.h
@brief PositionDrawComp
�S���ҁF�ێR �T��
*/

#include "PositionDrawComp.h"

#include "DebugObject.h"

namespace basecross {

	void PositionDrawComp::OnUpdate() {
		DebugObject::AddVector(transform->GetPosition());

	}

}

//endbasecross