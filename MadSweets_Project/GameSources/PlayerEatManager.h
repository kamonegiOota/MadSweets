#pragma once
#include"PlayerWeightManager.h"

namespace basecross
{
	class PlayerEatManager : public Component
	{
		ex_weak_ptr<PlayerWeightManager> m_weightManager;
	public:
		PlayerEatManager(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate() override {}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
	};
}