/*!
@file EnState_Plowling.cpp
@brief EnState_Plowling�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "EnState_LoseTarget.h"
#include "I_Escape.h"

#include "MyUtility.h"
#include "Velocity.h"
#include "EnemyRotationCtrl.h"
#include "EyeSearchRange.h"

#include "DebugObject.h"

namespace basecross {

	void TargetEscape::EyeSearch() {
		auto eye = GetGameObject()->GetComponent<EyeSearchRange>(false);
		if (eye) {
			if (eye->IsLookTarget(m_target)) {
				CalucNextNode();
				m_outSightCount = 0;
			}
		}
	}

	void TargetEscape::Rotation() {
		auto velocity = GetGameObject()->GetComponent<Velocity>(false);
		auto rotation = GetGameObject()->GetComponent<EnemyRotationCtrl>(false);
		if (velocity && rotation) {
			rotation->SetDirect(velocity->GetVelocity());
		}
	}

	void TargetEscape::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {  //Astar������������
			return;
		}

		astar->UpdateVelocityMove(GetVelocityMaxSpeed(),GetArriveNearRange());
		//DebugObject::sm_wss << L"es";
		if(astar->IsRouteEnd()) {  //�ŏI�ꏊ�܂ŏA������
			TargetRayCheck();
		}
	}

	void TargetEscape::TargetRayCheck() {
		//��Q������������
		if (maru::MyUtility::IsRayObstacle(GetGameObject(),m_target)) {
			m_outSightCount++;
		}
		else {  //����������
			m_outSightCount = 0;
		}

		ChangeStateCheck();
	}

	void TargetEscape::ChangeStateCheck() {
		if (m_outSightCount > m_alertReleaseNum) { //�w��񐔓����؂�����
			SuccessEscape(); //�����؂萬��
		}
		else {
			//���̃m�[�h�����ԉ����m�[�h��I������B
			CalucNextNode();
		}
	}

	void TargetEscape::CalucNextNode() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->SearchAstarEscapeNextRoute(m_target);  //���ɓ�����ׂ��m�[�h�̌���
		}
	}

	void TargetEscape::SuccessEscape() {  //�����؂萬��
		auto escape = GetGameObject()->GetComponent<I_Escape>();
		if (escape) {
			//DebugObject::sm_wss << endl << to_wstring(m_outSightCount) <<endl << L"escape";
			escape->SuccessEscape();
		}
	}

	void TargetEscape::OnCreate() {
		SetUpdateActive(false);
		SetArriveNearRange(1.0f);
		SetVelocityMaxSpeed(10.0f);
	}

	void TargetEscape::OnUpdate() {
		Move();  //�m�[�h�܂ňړ�
		Rotation();

		//�G�𔭌�������������T��
		EyeSearch();
	}

}

//endbasecross