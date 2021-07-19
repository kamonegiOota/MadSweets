#pragma once

namespace basecross
{
	class PlayerHideManager : public Component
	{
		bool m_isHide = false;
	public:
		PlayerHideManager(std::shared_ptr<GameObject>& owner);

		void OnUpdate() override;
	};
}