/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "ObjectTransport.h"

namespace basecross {

	void ObjectTransport::ParentSet() {
		auto target = m_target.lock();
		if (target == nullptr) {
			return;
		}

		target->SetParent(GetGameObject());
	}

	void ObjectTransport::OnCreate() {
		ParentSet();
	}

}

//endbasecross