#pragma once
#include"ChoicesComponentBase.h"

namespace basecross
{
	class I_EventComponent
	{
	public:
		virtual void OnEvent() = 0;
	};

	class EventedComponent : public ChoicesComponentBase
	{
		std::shared_ptr<ChoicesObjectAndEvent> m_choicesObjectAndEvent;
	public:
		EventedComponent(std::shared_ptr<GameObject>& owner); 

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}