/*!
@file AstarPlowlingMove.cpp
@brief AstarPlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "AstarPlowlingMove.h"
#include "EnemyRotationCtrl.h"
#include "Velocity.h"

#include "UtilVelocity.h"
#include "AstarCtrl.h"

namespace basecross {

	void AstarPlowlingMove::ChangeRoute() {
		auto toStartPos = m_param.startPos - transform->GetPosition();
		auto toEndPos = m_param.endPos - transform->GetPosition();

		//startPos�̕����߂�������
		if (toStartPos.length() < toEndPos.length()) {  
			m_astar->SearchAstarStart(m_param.endPos); //endPos�Ɍ�����
		}
		else {  //�����łȂ�������startPos�Ɍ�����
			m_astar->SearchAstarStart(m_param.startPos);
		}
	}

	void AstarPlowlingMove::Move() {
		m_astar->UpdateVelocityMove(m_param.maxSpeed, m_param.nearRange);
		m_param.returnPos = m_astar->GetCalucNodePos();  //�Ⴄ�X�e�[�g�ɂȂ����Ƃ��ɍŌ�Ɍ������m�[�h���L�^����B

		if (m_astar->IsRouteEnd()) {
			ChangeRoute();
		}
	}

	void AstarPlowlingMove::OnStart() {
		m_astar = GetGameObject()->GetComponent<AstarCtrl>(false);
	}

	void AstarPlowlingMove::OnUpdate() {
		if (!m_astar) {
			return;
		}

		Move();
	}

}

//endbasecross