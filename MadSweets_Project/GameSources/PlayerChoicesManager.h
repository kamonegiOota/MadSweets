#pragma once

namespace basecross
{
	class PlayerChoicesManager : public Component
	{
		ex_weak_ptr<ChoicesList> m_playerChoicesList;

		std::vector<ex_weak_ptr<GameObject>> m_rayCollisionObjects;

		float m_searchRange;

		bool m_isLocked = false;

		void ChoicesPushSound();

		void ChoicesSelectSound();

	public:
		PlayerChoicesManager(std::shared_ptr<GameObject>& owner);

		void SetSearchRange(const float searchRange);

		float GetSearchRange() const;

		/// <summary>
		/// ���ڑI������ǉ�����
		/// </summary>
		/// <param name="choicesObjectAndEvent">�I�����̃f�[�^</param>
		void AddPlayerChoice(const std::shared_ptr<ChoicesObjectAndEvent>& choicesObjectAndEvent);

		/// <summary>
		/// ���ڑI�������폜����
		/// </summary>
		/// <param name="choicesObject">�I�����̃I�u�W�F�N�g</param>
		void RemovePlayerChoice(const std::shared_ptr<GameObject>& choicesObject);

		void OnStart() override;

		void OnUpdate() override;
	};
}