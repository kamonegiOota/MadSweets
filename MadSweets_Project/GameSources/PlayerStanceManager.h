#pragma once

namespace basecross
{
	/// <summary>
	/// プレイヤーの体勢
	/// </summary>
	enum class PlayerStance
	{
		/// <summary>
		/// 立っている
		/// </summary>
		Stand,
		/// <summary>
		/// しゃがんでいる
		/// </summary>
		Crouch
	};

	class PlayerStanceManager : public Component
	{
		PlayerStance m_playerStance = PlayerStance::Stand;

		void PlayerStanceChange();
	public:
		PlayerStanceManager(std::shared_ptr<GameObject>& owner);

		PlayerStance GetPlayerStance() const;

		void OnCreate() override;

		void OnUpdate() override;
	};
}