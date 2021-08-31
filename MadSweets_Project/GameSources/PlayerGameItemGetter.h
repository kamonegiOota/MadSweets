#pragma once
#include"GottenComponent.h"

namespace basecross
{
	class PlayerGameItemGetter : public Component, public I_GetComponent
	{
		static std::vector<GameItem> sm_gameItems;
	public:
		PlayerGameItemGetter(std::shared_ptr<GameObject>& owner);

		void OnGetGameItem(const GameItem& gameItem) override;

		bool FindGameItem(const GameItem& findGameItem) const;
	};
}