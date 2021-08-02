#pragma once

namespace basecross
{
	class PlayerChoicesManager : public Component
	{
		ex_weak_ptr<ChoicesList> m_playerChoicesList;

		std::vector<ex_weak_ptr<GameObject>> m_rayCollisionObjects;

		float m_searchRange;

		bool m_isLocked = false;

	public:
		PlayerChoicesManager(std::shared_ptr<GameObject>& owner);

		void SetSearchRange(const float searchRange);

		float GetSearchRange() const;

		void OnStart() override;

		void OnUpdate() override;
	};
}