
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
		float m_speed;
		ChaseMode m_chaseMode = ChaseMode::Look;

		std::function<void(TargetChase&)> m_updateFunc;

		void LookMove();
		void LostCheck();

		void LostMove();
		void LookCheck();

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