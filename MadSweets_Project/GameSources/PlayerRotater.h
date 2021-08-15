#pragma once

namespace basecross
{
	class PlayerRotater : public Component
	{
		bool m_isRestrict = false;

		float m_restrictRadian = XM_PI;

		float m_defaultRadian = 0.0f;
	public:
		PlayerRotater(std::shared_ptr<GameObject>& owner);

		void Restrict(const float radian);

		void UnRestrict();

		void OnUpdate() override;
	};
}