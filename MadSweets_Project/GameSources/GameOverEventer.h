#pragma once

namespace basecross
{
	class GameOverEventer : public Component
	{
	public:
		GameOverEventer(std::shared_ptr<GameObject>& owner);

		void OnFadeOut();

		void OnRetry();

		void OnBackTitle();
	};
}