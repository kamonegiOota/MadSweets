#pragma once

namespace basecross
{
	class PlayerRotater : public Component
	{
	public:
		PlayerRotater(std::shared_ptr<GameObject>& owner);

		void OnUpdate() override;
	};
}