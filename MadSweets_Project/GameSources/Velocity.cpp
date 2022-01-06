
/*!
@file Velocity.cpp
@brief Velocityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "Velocity.h"
#include "Mathf.h"
#include "DebugObject.h"

#include "UtilVelocity.h"

//#include <directxmath.h>

namespace basecross {

	void Velocity::MaxVelocityCheck() {
		auto speed = m_velocity.length();

		speed = maru::Mathf::Min(speed,m_maxSpeed);
		m_velocity = m_velocity.GetNormalized() * speed;
	}

	void Velocity::MaxForceCheck() {
		auto speed = m_force.length();

		speed = maru::Mathf::Min(speed, m_maxForce);
		m_force = m_force.GetNormalized() * speed;
	}

	Vec3 Velocity::MaxSteerVecCheck(const Vec3& vec) {
		auto speed = vec.length();
		speed = maru::Mathf::Min(speed, m_maxSteer);

		return normalize(vec) * speed;
	}

	Vec3 Velocity::CalucSeekVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed) {
		Vec3 desiredVelocity = normalize(toVec) * maxSpeed;  //希望のベクトル
		return (desiredVelocity - velocity);
	}

	Vec3 Velocity::CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl) {
		//Vec3 toTarget = toVec;
		float dist = toVec.length();
		if (dist > 0) {
			//constexpr float DecelerationTweaker = 0.3f;  //減速値
			//float speed = dist / (decl * DecelerationTweaker);
			//speed = maru::Mathf::Clamp(speed, 0.0f ,maxSpeed);
			//speed = maru::Mathf::Min(speed,maxSpeed);
			//Vec3 desiredVelocity = toVec * speed / dist; //希望のベクトル
			//Vec3 desiredVelocity = toVec; //希望のベクトル
			//auto steerVec = desiredVelocity - velocity;  //ステアリングベクトル
			auto steerVec = UtilVelocity::CalucArriveVec(velocity,toVec,maxSpeed,decl);

			//auto steerVec = toVec - velocity;  //ステアリングベクトル
			return MaxSteerVecCheck(steerVec);  //最大値の制限
		}
		return Vec3(0, 0, 0);
	}

	void Velocity::Move() {
		if (m_velocity == Vec3(0.0f)) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = transform->GetPosition();
		pos += m_velocity * delta;
		transform->SetPosition(pos);

		m_force = Vec3(0.0f);
	}

	void Velocity::OnUpdate() {
		//速度の加算
		auto delta = App::GetApp()->GetElapsedTime();
		m_velocity += m_force * delta;

		Move(); //移動処理

		MaxVelocityCheck();  //最大速度管理
	}

	//void Velocity::SetForce(const Vec3& force) {
	//	//Vec3 newForce(0.0f);
	//	//if (force.length() <= m_nearRange) {  //距離が近かったら
	//	//	newForce = CalucArriveVec(m_velocity, force, m_maxSpeed); //ステアリングベクトル
	//	//}
	//	//else {   //距離が遠かったら
	//	//	newForce = CalucSeekVec(m_velocity, force, m_maxSpeed);  //シークベクトル
	//	//}

	//	m_force = force;  //力の更新

	//	MaxForceCheck();     //力の最大値チェック
	//}

}

//endbasecross