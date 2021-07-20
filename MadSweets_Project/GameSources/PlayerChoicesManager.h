#pragma once

namespace basecross
{
	class PlayerChoicesManager : public Component
	{
		ex_weak_ptr<GameObject> m_playerCameraObject;

		ex_weak_ptr<ChoicesList> m_playerChoicesList;

		std::vector<ex_weak_ptr<GameObject>> m_rayCollisionObjects;

		float m_searchRange;

		template<class T>
		bool IsContains(const std::vector<T>& vector,const T& item) const
		{
			return std::find(vector.begin(), vector.end(), item) != vector.end();
		}

	public:
		PlayerChoicesManager(std::shared_ptr<GameObject>& owner,const std::shared_ptr<GameObject>& playerCamera);

		void SetSearchRange(const float searchRange);

		float GetSearchRange() const;

		void OnStart() override;

		void OnUpdate() override;
	};
}