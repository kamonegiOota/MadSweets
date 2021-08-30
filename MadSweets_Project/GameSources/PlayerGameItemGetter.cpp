#include"PlayerGameItemGetter.h"

namespace basecross
{
	PlayerGameItemGetter::PlayerGameItemGetter(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerGameItemGetter::OnGetGameItem(const GameItem& gameItem)
	{
		m_gameItems.push_back(gameItem);
	}

	bool PlayerGameItemGetter::FindGameItem(const GameItem& findGameItem) const
	{
		for (const auto& gameItem : m_gameItems)
		{
			if (gameItem == findGameItem)
			{
				return true;
			}
		}

		return false;
	}
}