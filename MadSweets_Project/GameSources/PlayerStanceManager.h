#pragma once

namespace basecross
{
	/// <summary>
	/// ƒvƒŒƒCƒ„[‚Ì‘Ì¨
	/// </summary>
	enum class PlayerStance
	{
		/// <summary>
		/// —§‚Á‚Ä‚¢‚é
		/// </summary>
		Stand,
		/// <summary>
		/// ‚µ‚á‚ª‚ñ‚Å‚¢‚é
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