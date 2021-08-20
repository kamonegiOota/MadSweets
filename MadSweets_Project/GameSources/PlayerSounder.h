#pragma once

namespace basecross
{
	class PlayerSounder : public Component
	{
	public:
		PlayerSounder(std::shared_ptr<GameObject>& owner);

		void PlayerWalk();
	};
}