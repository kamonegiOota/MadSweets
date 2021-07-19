#pragma once

namespace basecross
{
	class HiddenComponent : public Component
	{
		Vec3 m_hiddenWorldPosition;
	public:
		HiddenComponent(std::shared_ptr<GameObject>& owner,const Vec3& hiddenWorldPosition);

		Vec3 GetHiddenWorldPosition() const;
	};
}