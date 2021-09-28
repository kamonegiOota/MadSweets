
/*!
@file TargetChase.h
@brief TargetChase
担当者：丸山 裕喜
*/

#pragma once

#include "TargetMgr.h"

namespace basecross {

	//設定されたターゲットを追従する処理
	class TargetChase : public Component
	{
		enum class ChaseMode {
			Look,  //視認できている状態
			Lost   //視認できてない状態
		};

		ex_weak_ptr<GameObject> m_target;
		ChaseMode m_chaseMode = ChaseMode::Look;
		float m_maxSpeed = 10.0f;

		std::function<void(TargetChase&)> m_updateFunc;

		bool m_isEnd = false;

		/// <summary>
		/// 視界の先に隠れるオブジェクトが合って、そこにtargetが隠れていたらそれをターゲットにする。
		/// </summary>
		/// <returns>視界の先に隠れるオブジェクトがあればtrue</returns>
		bool TargetEyeRangeHide();
		/// <summary>
		/// ターゲットを見失った時
		/// </summary>
		void LostTarget();  
		/// <summary>
		/// ターゲットを見つけた時
		/// </summary>
		void FindTarget();

		/// <summary>
		/// 視界の中にターゲットがいる時の移動
		/// </summary>
		void LookMove();
		/// <summary>
		/// 視界の外にターゲットがいる時の移動
		/// </summary>
		void LostMove();

		/// <summary>
		/// 視界内にいるかチェックし、それに合わせて状態を変える。
		/// </summary>
		void LookCheck();

		void Rotation(const Vec3& moveVec);

		void ChangeStateMachine();

	public:
		TargetChase(const std::shared_ptr<GameObject>& objPtr);

		TargetChase(const std::shared_ptr<GameObject>& objPtr, const float& speed);

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}

		/// <summary>
		/// 追う処理の開始
		/// </summary>
		void ChaseStart() {
			m_isEnd = false;
			m_chaseMode = ChaseMode::Look;
			m_updateFunc = &TargetChase::LookMove;
			
			auto targetMgr = GetGameObject()->GetComponent<TargetMgr>(false);
			if (targetMgr) {
				m_target = targetMgr->GetTarget();
			}
		}

		//アクセッサ-----------------------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target.GetShard();
		}

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

		bool IsEnd() {
			return m_isEnd;
		}

	};

}

//endbasecross