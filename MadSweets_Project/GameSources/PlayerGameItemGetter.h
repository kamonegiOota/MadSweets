#pragma once
#include"GottenComponent.h"

namespace basecross
{
	class PlayerGameItemGetter : public Component, public I_GetComponent
	{
		std::vector<GameItem> m_gameItems;
	public:
		PlayerGameItemGetter(std::shared_ptr<GameObject>& owner);

		void OnGetGameItem(const GameItem& gameItem) override;

		bool FindGameItem(const GameItem& findGameItem) const;
	};
}