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
		/// 直接選択肢を追加する
		/// </summary>
		/// <param name="choicesObjectAndEvent">選択肢のデータ</param>
		void AddPlayerChoice(const std::shared_ptr<ChoicesObjectAndEvent>& choicesObjectAndEvent);

		/// <summary>
		/// 直接選択肢を削除する
		/// </summary>
		/// <param name="choicesObject">選択肢のオブジェクト</param>
		void RemovePlayerChoice(const std::shared_ptr<GameObject>& choicesObject);

		void OnStart() override;

		void OnUpdate() override;
	};
}