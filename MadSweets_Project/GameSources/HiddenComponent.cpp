#include"HiddenComponent.h"

namespace basecross
{
	HiddenComponent::HiddenComponent(std::shared_ptr<GameObject>& owner, const Vec3& hiddenWorldPosition) :
		Component(owner),
		m_hiddenWorldPosition(hiddenWorldPosition)
	{
	}

	Vec3 HiddenComponent::GetHiddenWorldPosition() const
	{
		return m_hiddenWorldPosition;
	}
}