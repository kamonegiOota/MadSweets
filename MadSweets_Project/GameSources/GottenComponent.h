#pragma once
#include"ChoicesComponentBase.h"
#include"GameItem.h"

namespace basecross
{
	class I_GetComponent
	{
	public:
		virtual void OnGetGameItem(const GameItem& gameItem) = 0;
	};

	class GottenComponent : public ChoicesComponentBase
	{
		bool m_isGottenDestroy;

		GameItem m_gameItem;

		std::shared_ptr<ChoicesObjectAndEvent> m_choicesObjectAndEvent;

	public:
		itbs::Utility::Delegate<void()> gottenEvent;

		GottenComponent(std::shared_ptr<GameObject>& owner, const GameItem& gameItem, const bool isGottenDestroy = true);

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}