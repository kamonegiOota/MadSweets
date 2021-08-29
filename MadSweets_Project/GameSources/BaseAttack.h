/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// 攻撃パラメータの構造体
	/// </summary>
	struct AttackParam {
		float range = 1.0f;
		float power = 1.0f;

		AttackParam()
			:AttackParam(1.0f,1.0f)
		{}

		AttackParam(const float& range,
			const float& power
		):
			range(range),
			power(power)
		{}
	};

	class BaseAttack : public Component
	{
	protected:

		std::shared_ptr<GameObject> m_target;
		bool m_isAttack = false;
		AttackParam m_param;

		/// <summary>
		/// ターゲットが範囲内にいるかどうか判断
		/// </summary>
		/// <param name="isObstacleChek">障害物チェックをするかどうか</param>
		/// <returns>範囲内ならtrueを返す</returns>
		virtual bool IsAttackRange(const bool isObstacleChek = true);

		virtual void ChangeAttackState() = 0;
		virtual void ChangeEndState() = 0;

	public:

		BaseAttack(const std::shared_ptr<GameObject>& objPtr)
			:BaseAttack(objPtr,AttackParam())
		{}

		BaseAttack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param
		):
			Component(objPtr),m_param(param)
		{}

		virtual void OnCreate() override{}
		virtual void OnUpdate() override{}

		virtual void Attack(const std::shared_ptr<GameObject>& target) = 0;

		//アクセッサ-------------------------------------------------

		//ターゲットのセット
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

		//攻撃範囲
		void SetRange(const float& range) {
			m_param.range = range;
		}
		float GetRange() const {
			return m_param.range;
		}
		
		//攻撃力
		void SetAttackPower(const float& power) {
			m_param.power = power;
		}
		float GetAttackPower() const {
			return m_param.power;
		}
	};

}

//endbasecross