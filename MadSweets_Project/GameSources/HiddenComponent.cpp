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

	HideData HiddenComponent::GetHideData() const
	{
		return m_hideData;
	}

	std::shared_ptr<ChoicesObjectAndEvent const> HiddenComponent::GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject)
	{
		auto hideComponent = selectorObject->GetComponent<I_HideComponent>(false);

		auto& hideData = m_hideData;
		auto eventFunction = [hideComponent, &hideData]() {hideComponent->OnHide(hideData); };

		m_choicesObjectAndEvent = std::make_shared<ChoicesObjectAndEvent>(L"‰B‚ê‚é", GetGameObject(), eventFunction);

		return m_choicesObjectAndEvent;
	}

	void HiddenComponent::Damage(const float& damage) {
		auto damageComp = m_hideData.hideObject->GetComponent<I_Damaged>(false);
		if (damageComp) {
			damageComp->Damage(damage);
		}
		//GetStage()->RemoveGameObject<GameObject>(GetGameObject());
	}
}