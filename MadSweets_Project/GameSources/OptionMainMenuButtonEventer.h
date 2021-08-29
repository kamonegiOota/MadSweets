#pragma once

namespace basecross
{
	class OptionMainMenuButtonEventer : public Component
	{
		ex_weak_ptr<GameObject> m_subOptionMenu;

		bool m_isGoSubMenu = false;
	public:
		OptionMainMenuButtonEventer(std::shared_ptr<GameObject>& owner, const std::shared_ptr<GameObject>& subOptionMenu);

		void OnSelect();

		void OnPush();

		void OnoutSelect();

		void OnStart() override;
	};
}