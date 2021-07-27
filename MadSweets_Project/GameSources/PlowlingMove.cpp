/*!
@file PlowlingMove.cpp
@brief PlowlingMoveなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "PlowlingMove.h"
#include "EnemyRotationCtrl.h"
#include "Velocity.h"

#include "UtilVelocity.h"

namespace basecross {

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr) :
		PlowlingMove(objPtr, std::vector<Vec3>())
	{}

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
		const std::vector<Vec3>& positions
	) :
		PlowlingMove(objPtr,positions,2.0f,10.0f)
	{}

	PlowlingMove::PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
		const std::vector<Vec3>& positions,
		const float& speed,
		const float& nearRange
	):
		Component(objPtr),
		m_positions(positions),
		m_index(0),
		m_addIndexDirect(1),
		m_maxSpeed(speed),
		m_nearRange(nearRange)
	{}


	Vec3 PlowlingMove::CalucMoveVec() {
		auto selfPos = transform->GetPosition();
		auto movePos = m_positions[m_index] - selfPos;

		return movePos;
	}

	void PlowlingMove::Move() {
		auto velocityComp = GetGameObject()->GetComponent<Velocity>();
		if (!velocityComp) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		auto moveVec = CalucMoveVec();

		//実際の速度の計算
		auto velocity = velocityComp->GetVelocity();
		auto force = UtilVelocity::CalucNearArriveFarSeek(velocity, moveVec, m_maxSpeed, m_nearRange);

		velocityComp->SetForce(force);

		Rotation(moveVec);

		if (IsNearArrival(transform->GetPosition())) {   //目的地に到達していたら
			NextIndex();
		}
	}

	void PlowlingMove::Rotation(const Vec3& moveVec) {
		auto rotCtrl = GetGameObject()->GetComponent<EnemyRotationCtrl>();
		rotCtrl->SetDirect(moveVec);
	}

	bool PlowlingMove::IsNearArrival(const Vec3& pos) {
		float nearRange = 0.1f;  //近くまで来たら、次のポジションに移動するようにする。

		auto toTargetVec = m_positions[m_index] - pos;
		//目的地に到着していたらtrue
		return toTargetVec.length() <= nearRange ? true : false;
	}

	void PlowlingMove::NextIndex() {
		m_index += m_addIndexDirect; //カウントを進める。

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