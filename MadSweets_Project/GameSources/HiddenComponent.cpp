#include"HiddenComponent.h"

namespace basecross
{
	// HideData -------------------------------------

	HideData::HideData() : HideData(Vec3(), Vec3(0, 0, 1)) {}

	HideData::HideData(const Vec3& hideWorldPosition, const Vec3& hideForward) :
		hideWorldPosition(hideWorldPosition),
		hideForward(hideForward)
	{

	}

	// HiddenComponet -------------------------------

	HiddenComponent::HiddenComponent(std::shared_ptr<GameObject>& owner, const Vec3& hideWorldPosition, const Vec3& hideForward) :
		HiddenComponent(owner, HideData(hideWorldPosition, hideForward))
	{
	}

	HiddenComponent::HiddenComponent(std::shared_ptr<GameObject>& owner, const HideData& hideData) :
		ChoicesComponentBase(owner),
		m_hideData(hideData)
	{

	}

	void HiddenComponent::ChangeHidden(const bool isHidden)
	{
		m_isHidden = isHidden;

		if (isHidden)
		{
			m_choicesObjectAndEvent->text = L"o‚é";
		}
		else
		{
			m_choicesObjectAndEvent->text = L"‰B‚ê‚é";
		}
	}

	HideData HiddenComponent::GetHideData() const
	{
		return m_hideData;
	}

	std::shared_ptr<ChoicesObjectAndEvent const> HiddenComponent::GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject)
	{
		auto hideComponent = selectorObject->GetComponent<I_HideComponent>(false);

		std::function<void()> eventFunction = []() {};

		if (hideComponent)
		{
			eventFunction = [&,hideComponent]()
			{
				if (m_isHidden)
				{
					hideComponent->OnEndHide(m_hideData);
				}
				else
				{
					hideComponent->OnHide(m_hideData);
				}

				ChangeHidden(!m_isHidden);
			};
		}

		if (m_choicesObjectAndEvent)
		{
			m_choicesObjectAndEvent->eventFunction = eventFunction;
			return m_choicesObjectAndEvent;
		}

		m_choicesObjectAndEvent = std::make_shared<ChoicesObjectAndEvent>(L"‰B‚ê‚é", GetGameObject(), eventFunction);

		return m_choicesObjectAndEvent;
	}
}