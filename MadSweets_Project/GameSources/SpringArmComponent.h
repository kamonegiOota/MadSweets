#pragma once

namespace basecross
{
	class SpringArmComponent : public Component
	{
		ex_weak_ptr<GameObject> m_childObject;

		ex_weak_ptr<Transform> m_childTransform;

		float m_armRange = 10.0f;

		std::vector<std::wstring> m_hitTags;

		Vec3 m_direction;
	public:
		SpringArmComponent(std::shared_ptr<GameObject>& owner);

		void SetArmRange(const float armRange);

		float GetArmRange() const;

		void AddHitTag(const std::wstring& hitTag);

		void RemoveHitTag(const std::wstring& hitTag);

		void SetChildObject(const std::shared_ptr<GameObject>& childObject);

		void OnUpdate() override;
	};
}