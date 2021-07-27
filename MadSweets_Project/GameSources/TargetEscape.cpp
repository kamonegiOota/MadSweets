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

#include "DebugObject.h"

namespace basecross {

	void TargetEscape::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {  //Astar������������
			return;
		}

		astar->UpdateMove();
		
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

	void TargetEscape::SuccessEscape() {
		auto escape = GetGameObject()->GetComponent<I_Escape>();
		if (escape) {
			DebugObject::m_wss << endl << to_wstring(m_outSightCount) <<endl << L"escape";
			escape->SuccessEscape();
		}
	}

	void TargetEscape::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetEscape::OnUpdate() {
		Move();  //�m�[�h�܂ňړ�

		//�ړ�������G�Ƃ̏�Ԃ����� 
				
		//��Q�������Ԃ�����(���)�������猳�ɖ߂�
		
		//�����łȂ��ꍇ�́A���̃m�[�h�����ԉ����m�[�h��I�����Ĉړ�
	}

}

//endbasecross