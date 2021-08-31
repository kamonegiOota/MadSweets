#include"PlayerGameItemGetter.h"

namespace basecross
{
	std::vector<GameItem> PlayerGameItemGetter::sm_gameItems;

	PlayerGameItemGetter::PlayerGameItemGetter(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerGameItemGetter::OnGetGameItem(const GameItem& gameItem)
	{
		sm_gameItems.push_back(gameItem);
	}

	bool PlayerGameItemGetter::FindGameItem(const GameItem& findGameItem) const
	{
		for (const auto& gameItem : sm_gameItems)
		{
			if (gameItem == findGameItem)
			{
				return true;
			}
		}

		return false;
	}
}