#pragma once
#include"PlayerCalorieManager.h"
#include"AnimationHelper.h"
#include"PlayerObject.h"

namespace basecross
{
	class PlayerMover : public Component
	{
		float rotY = 0.0f;

		float m_standMoveSpeed;
		float m_crouchMoveSpeed;
		float m_dashPower;

		float m_dashUseWeight;

		bool m_isCameraAffected = false;

		ex_weak_ptr<PlayerCalorieManager> m_playerCalorieManager;

		ex_weak_ptr<Camera> m_camera;

		ex_weak_ptr<Animator<PlayerAnimationMember, PlayerState>> m_animator;
	public:
		PlayerMover(std::shared_ptr<GameObject>& owner);

		void SetMoveSpeed(const float moveSpeed);

		float GetMoveSpeed() const;

		void SetDashPower(const float dashPower);

		float GetDashPower() const;

		void SetIsCameraAffected(const bool isCameraAffected);

		bool GetIsCameraAffected() const;

		void OnStart() override;

		void OnUpdate() override;
	};
}