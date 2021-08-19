
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "Mathf.h"
#include "DebugObject.h"

namespace basecross {

	class Velocity : public Component
	{
		Vec3 m_force = Vec3(0.0f);
		Vec3 m_velocity = Vec3(0.0f);
		float m_maxSpeed = 4.0f;
		float m_maxForce = 10.0f;
		float m_maxSteer = 3.0f;  //数字が大きいほど旋回しやすい
		float m_nearRange = 1.0f; //近いと判断される距離
		
		//最高速度の調整
		/// <summary>
		/// 最大速度制限
		/// </summary>
		void MaxVelocityCheck();
		/// <summary>
		/// 最大Force制限
		/// </summary>
		void MaxForceCheck();
		/// <summary>
		/// 一度に加算されるベクトルの最大値制限
		/// </summary>
		Vec3 MaxSteerVecCheck(const Vec3& vec);  //一度に加算される最大値の制限

		//ベクトル計算用の関数。
		/// <summary>
		/// ターゲットの方向のベクトルを現在の速度で引いたベクトルを返す。
		/// </summary>
		/// <param name="velocity">現在の速度</param>
		/// <param name="toVec">ターゲット方向のベクトル</param>
		/// <param name="maxSpeed">最大速度</param>
		/// <returns>「ターゲットの方向のベクトル」- 「現在の速度」</returns>
		Vec3 CalucSeekVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed);
		/// <summary>
		/// 到着ベクトルを返す(近づくと小さくなるベクトル)
		/// </summary>
		/// <param name="velocity">現在の速度</param>
		/// <param name="toVec">ターゲット方向のベクトル</param>
		/// <param name="maxSpeed">最大速度</param>
		/// <param name="decl"></param>
		/// <returns>到着ベクトルを返す(近づくと小さくなるベクトル)を返す</returns>
		Vec3 CalucArriveVec(const Vec3& velocity, const Vec3& toVec, float maxSpeed, float decl = 3.0f);

		void Move();

	public:

		Velocity(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;

		//アクセッサ-----------------------------------------------------------

		void Reset() {
			m_force = Vec3(0.0f);
			m_velocity = Vec3(0.0f);
		}

		void AddForce(const Vec3& force) {
			m_force += force;
			MaxForceCheck();
		}

		void SetForce(const Vec3& force) {
			m_force = force;  //力の更新
			MaxForceCheck();     //力の最大値チェック
		}
		Vec3 GetForce() const {
			return m_force;
		}

		//void AddVelocity(const Vec3& velocity) {
		//	m_velocity += velocity;
		//}

		void SetVelocity(const Vec3& velocity) {
			m_velocity = velocity;
		}
		Vec3 GetVelocity() const {
			return m_velocity;
		}

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

		/// <summary>
		/// 旋回しやすさが変わる変数(Default値は3.0f)
		/// </summary>
		/// <param name="steer">変えたい旋回しやすさ</param>
		void SetMaxSteer(const float& steer) {
			m_maxSteer = steer;
		}
		/// <summary>
		/// 旋回しやすさが変わる変数(Default値は3.0f)
		/// </summary>
		/// <returns>現在の旋回しやすさ</returns>
		float GetMaxSteer() const {
			return m_maxSteer;
		}

		/// <summary>
		/// 対象から近いと判断される距離
		/// </summary>
		/// <param name="range">近いと判断される距離</param>
		void SetNearRange(const float& range) {
			m_nearRange = range;
		}
		/// <summary>
		/// 現在の対象から近いと判断される距離
		/// </summary>
		/// <returns>現在の対象から近いと判断される距離</returns>
		float GetNearRange() const {
			return m_nearRange;
		}

		//void AddForce(Vec3 force) {
		//	//m_force += force;

		//	auto newDot = dot(m_force.GetNormalized(),force.GetNormalized());
		//	auto rad = acosf(newDot);

		//	//DebugObject::m_wss << to_wstring(XMConvertToDegrees(rad));
		//	//DebugObject::sm_isResetDelta = true;

		//	if (rad >= XMConvertToRadians(5.0f)) {
		//		m_force += force;
		//	}
		//	else {
		//		m_force += force;
		//	}

		//	MaxForceCheck();
		//}

		//bool AccumulateForce(bsm::Vec3& Force, const bsm::Vec3& ForceToAdd, float MaxForce) {
		//	//現在の力の長さを得る
		//	float MagnitudeSoFar = bsm::length(Force);
		//	//最大値との差を求める
		//	float magnitudeRemaining = MaxForce - MagnitudeSoFar;
		//	//差が0以下（つまり最大値を超えていたら）
		//	//追加しないでリターン
		//	if (magnitudeRemaining <= 0.0f) {
		//		return false;
		//	}
		//	//追加する力の大きさを求める
		//	float MagnitudeToAdd = bsm::length(ForceToAdd);
		//	//力の追加
		//	if (MagnitudeToAdd < magnitudeRemaining) {
		//		Force += ForceToAdd;
		//	}
		//	else {
		//		Force += (bsm::normalize(ForceToAdd) * MagnitudeToAdd);
		//	}
		//	//追加された指標を返す  
		//	return true;
		//}
	};

}

//endbasecross