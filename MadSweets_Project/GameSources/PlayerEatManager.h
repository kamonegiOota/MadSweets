#pragma once
#include"PlayerCalorieManager.h"

namespace basecross
{
	class PlayerEatManager : public Component
	{
		ex_weak_ptr<PlayerCalorieManager> m_calorieManager;

		ex_weak_ptr<GameObject> m_playerCameraObject;

		float m_searchRange = 1;
	public:
		PlayerEatManager(std::shared_ptr<GameObject>& owner,std::shared_ptr<GameObject> playerCamera);

		void OnCreate() override;

		void OnUpdate() override;

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
	};
}