#pragma once

namespace basecross
{
	class PlayerMover : public Component
	{
		float rotY = 0.0f;
	public:
		PlayerMover(std::shared_ptr<GameObject>& owner);

		void OnUpdate() override;

		void OnDraw() override {}
	};
}