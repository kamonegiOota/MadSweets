/*!
@file PlowlingMove.cpp
@brief PlowlingMove�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "PlowlingMove.h"
#include "EnemyRotationCtrl.h"
#include "Velocity.h"
#include "AstarCtrl.h"

#include "UtilVelocity.h"

namespace basecross {

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr) :
		PlowlingMove(objPtr, std::vector<Vec3>())
	{}

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
		const std::vector<Vec3>& positions
	):
		Component(objPtr),
		m_positions(positions),
		m_index(0),
		m_addIndexDirect(1)
	{}


	Vec3 PlowlingMove::CalucMoveVec() {
		auto selfPos = transform->GetPosition();
		auto movePos = m_positions[m_index] - selfPos;

		return movePos;
	}

	void PlowlingMove::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		astar->UpdateVelocityMove(GetVelocityMaxSpeed(), GetVelocityMaxSpeed());

		if (astar->IsRouteEnd()) {
			NextIndex();
		}
	}

	void PlowlingMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>();
		rotCtrl->SetDirect(moveVec);
	}

	void PlowlingMove::NextIndex() {
		m_index += m_addIndexDirect; //�J�E���g��i�߂�B

		if (m_index >= m_positions.size() || m_index < 0) {
			m_addIndexDirect *= -1;  //�J�E���g��i�߂�������t�ɂ���B
			m_index += m_addIndexDirect;
		}

		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		astar->SearchAstarStart(m_positions[m_index]);
	}

	void PlowlingMove::OnCreate() {
		SetVelocityMaxSpeed(2.0f);
		SetArriveNearRange(3.5f);
	}

	void PlowlingMove::OnStart() {

	}

	void PlowlingMove::OnUpdate() {
		if (m_positions.size() == 0) {  //�p�j����ꏊ���Ȃ��ꍇ�͏������s��Ȃ��B
			return;
		}

		Move();
	}

}

//endbasecross