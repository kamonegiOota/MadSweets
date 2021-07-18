
/*!
@file TargetChase.h
@brief TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	//�ݒ肳�ꂽ�^�[�Q�b�g��Ǐ]���鏈��
	class TargetChase : public Component
	{
		enum class ChaseMode {
			Look,  //���F�ł��Ă�����
			Lost   //���F�ł��ĂȂ����
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

		//�A�N�Z�b�T-----------------------------------------------------------------------
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