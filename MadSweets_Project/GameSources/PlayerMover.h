#pragma once

namespace basecross
{
	class PlayerMover : public Component
	{
		float rotY = 0.0f;

		float m_moveSpeed;
		float m_dashPower;
	public:
		PlayerMover(std::shared_ptr<GameObject>& owner);

		void SetMoveSpeed(const float moveSpeed);

		float GetMoveSpeed() const;

		void SetDashPower(const float dashPower);

		float GetDashPower() const;

		void OnUpdate() override;

		void OnDraw() override {}
	};
}