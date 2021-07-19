/*!
@file PositionDrawComp.h
@brief PositionDrawComp
’S“–ŽÒFŠÛŽR —TŠì
*/

#include "PositionDrawComp.h"

#include "DebugObject.h"

namespace basecross {

	void PositionDrawComp::OnUpdate() {
		DebugObject::AddVector(transform->GetPosition());

	}

}

//endbasecross