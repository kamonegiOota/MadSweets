
/*!
@file ThrowObject.cpp
@brief ThrowObject�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowObject.h"
#include "ThrowObjectCtrl.h"
#include "Velocity.h"

namespace basecross {

	void ThrowObject::OnCreate() {
		//�����I�ɂ͌����ڂ̂ݏ���
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<ThrowObjectCtrl>();
		AddComponent<Velocity>();
	}

}

//endbasecross