/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
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

		if (IsNextIndex(pos)) {   //次のインデックスになったら
			NextIndex();
		}
	}

	bool PlowlingMove::IsNextIndex(const Vec3& pos) {
		float nearRange = 0.1f;  //近くまで来たら、次のポジションに移動するようにする。

		auto toTargetVec = m_positions[m_index] - pos;
		//目的地に到着していたらtrue
		return toTargetVec.length() <= nearRange ? true : false;
	}

	void PlowlingMove::NextIndex() {
		m_index += m_addIndexDirect;

		if (m_index >= m_positions.size() || m_index < 0) {
			m_addIndexDirect *= -1;  //カウントを進める方向を逆にする。
			m_index += m_addIndexDirect;
		}
	}

	void PlowlingMove::OnUpdate() {
		if (m_positions.size() == 0) {  //徘徊する場所がない場合は処理を行わない。
			return;
		}

		Move();
	}

}

//endbasecross