#pragma once

namespace basecross
{
	class OptionMenuEventer : public Component
	{
	public:
		OptionMenuEventer(std::shared_ptr<GameObject>& owner);

		void OnFadeOut();

		void GoTitleStage();

		void OnBackMainOptionMenu();

		void OnUpdate() override;
	};
}