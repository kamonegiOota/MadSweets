
/*!
@file BillBoard.cpp
@brief BillBoard�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "BillBoard.h"

#include "MyUtility.h"

namespace basecross {

	void BillBoard::OnCreate() {

	}

	void BillBoard::OnUpdate() {
		// �J�������擾����
		auto camera = dynamic_pointer_cast<Camera>(GetStage()->GetView()->GetTargetCamera());

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		// �J�����ւ̉�]���Z�o����
		auto boardToCamera = camera->GetEye() - pos;
		//boardToCamera.y = 0.0f;
		boardToCamera.normalize();
		float rotY = atan2f(-boardToCamera.z, boardToCamera.x) + m_forwardAdjust;

		transComp->SetRotation(0.0f, rotY, 0.0f);
		transComp->SetPosition(pos);
	}

}

//endbasecross