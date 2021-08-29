
/*!
@file BillBoard.cpp
@brief BillBoardクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "BillBoard.h"

#include "MyUtility.h"

namespace basecross {

	void BillBoard::OnCreate() {

	}

	void BillBoard::OnUpdate() {
		// カメラを取得する
		auto camera = dynamic_pointer_cast<Camera>(GetStage()->GetView()->GetTargetCamera());

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		// カメラへの回転を算出する
		auto boardToCamera = camera->GetEye() - pos;
		//boardToCamera.y = 0.0f;
		boardToCamera.normalize();
		float rotY = atan2f(-boardToCamera.z, boardToCamera.x) + m_forwardAdjust;

		transComp->SetRotation(0.0f, rotY, 0.0f);
		transComp->SetPosition(pos);
	}

}

//endbasecross