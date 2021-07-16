#pragma once
#include"PlayerStanceManager.h"

namespace basecross
{

	class PlayerProvider : public Component
	{
	public:
		PlayerProvider(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate() override;

		void OnDraw() override {}
	};
}