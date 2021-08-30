#include"EventedComponent.h"

namespace basecross
{
	EventedComponent::EventedComponent(std::shared_ptr<GameObject>& owner) :
		ChoicesComponentBase(owner)
	{

	}

	std::shared_ptr<ChoicesObjectAndEvent const> EventedComponent::GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject)
	{
		auto eventComponent = selectorObject->GetComponent<I_EventComponent>(false);

		auto eventFunction = [eventComponent]()
		{
			eventComponent->OnEvent();
		};

		m_choicesObjectAndEvent = std::make_shared<ChoicesObjectAndEvent>(L"ŠJ‚¯‚é", GetGameObject(), eventFunction);

		return m_choicesObjectAndEvent;
	}

}