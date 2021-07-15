
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
		std::shared_ptr<GameObject> m_target;

		float m_speed;

		void Move();

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