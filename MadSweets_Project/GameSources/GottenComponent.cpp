#include"GottenComponent.h"

namespace basecross
{
	GottenComponent::GottenComponent(std::shared_ptr<GameObject>& owner, const GameItem& gameItem, const bool isGottenDestroy) :
		ChoicesComponentBase(owner),
		m_gameItem(gameItem),
		m_isGottenDestroy(isGottenDestroy)
	{

	}

	std::shared_ptr<ChoicesObjectAndEvent const> GottenComponent::GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject)
	{
		auto getComponent = selectorObject->GetComponent<I_GetComponent>(false);

		auto eventFunction = [this,getComponent]()
		{
			getComponent->OnGetGameItem(m_gameItem);
			
			if (m_isGottenDestroy)
			{
				GetGameObject()->Destroy();
			}
		};

		m_choicesObjectAndEvent = std::make_shared<ChoicesObjectAndEvent>(L"èäìæÇ∑ÇÈ", GetGameObject(), eventFunction);

		return m_choicesObjectAndEvent;
	}
}