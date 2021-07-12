/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "PlowlingMove.h"

namespace basecross {

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr) :
		PlowlingMove(objPtr, std::vector<Vec3>())
	{}

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
		const std::vector<Vec3>& positions
	) :
		PlowlingMove(objPtr,positions,1.0f)
	{}

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
		const std::vector<Vec3>& positions,
		const float& speed
	):
		Component(objPtr),
		m_positions(positions),
		m_index(0),
		m_addIndexDirect(1),
		m_speed(speed)
	{}



	Vec3 PlowlingMove::CalucMoveVec() {
		auto selfPos = transform->GetPosition();
		auto movePos = m_positions[m_index] - selfPos;

		return movePos;
	}

	void PlowlingMove::Move() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto moveVec = CalucMoveVec();
		auto pos = transform->GetPosition();
		pos += moveVec.GetNormalized() * delta * m_speed;

		transform->SetPosition(pos);

		if (IsNextIndex(pos)) {   //���̃C���f�b�N�X�ɂȂ�����
			NextIndex();
		}
	}

	bool PlowlingMove::IsNextIndex(const Vec3& pos) {
		float nearRange = 0.1f;  //�߂��܂ŗ�����A���̃|�W�V�����Ɉړ�����悤�ɂ���B

		auto toTargetVec = m_positions[m_index] - pos;
		//�ړI�n�ɓ������Ă�����true
		return toTargetVec.length() <= nearRange ? true : false;
	}

	void PlowlingMove::NextIndex() {
		m_index += m_addIndexDirect;

		if (m_index >= m_positions.size() || m_index < 0) {
			m_addIndexDirect *= -1;  //�J�E���g��i�߂�������t�ɂ���B
			m_index += m_addIndexDirect;
		}
	}

	void PlowlingMove::OnUpdate() {
		if (m_positions.size() == 0) {  //�p�j����ꏊ���Ȃ��ꍇ�͏������s��Ȃ��B
			return;
		}

		Move();
	}

}

//endbasecross