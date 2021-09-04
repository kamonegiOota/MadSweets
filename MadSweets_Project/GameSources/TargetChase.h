
/*!
@file TargetChase.h
@brief TargetChase
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	//設定されたターゲットを追従する処理
	class TargetChase : public Component
	{
		enum class ChaseMode {
			Look,  //視認できている状態
			Lost   //視認できてない状態
		};

		std::shared_ptr<GameObject> m_target;
		ChaseMode m_chaseMode = ChaseMode::Look;
		float m_speed = 3.0f;

		std::function<void(TargetChase&)> m_updateFunc;

		//視界の先に隠れるオブジェクトが合ってそこにtargetが隠れていたらそれをターゲットにする。
		bool TargetEyeRangeHide();
		//ターゲットを見失った時
		void LostTarget();  
		//ターゲットを見つけた時
		void FindTarget();

		void LookMove();
		void LostMove();

		void LookCheck();

		void Rotation(const Vec3& moveVec);

		void ChangeStateMachine();

	public:
		TargetChase(const std::shared_ptr<GameObject>& objPtr);

		TargetChase(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<GameObject>& target
		);

		TargetChase(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<GameObject>& target,
			const float& speed
		);

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}

		//追う処理の開始
		void ChaseStart() {
			m_chaseMode = ChaseMode::Look;
			m_updateFunc = &TargetChase::LookMove;
		}

		//アクセッサ-----------------------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}
	};

}

//endbasecross