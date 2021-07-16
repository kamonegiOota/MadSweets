#pragma once

namespace basecross
{
	/// <summary>
	/// �v���C���[�̑̐�
	/// </summary>
	enum class PlayerStance
	{
		/// <summary>
		/// �����Ă���
		/// </summary>
		Stand,
		/// <summary>
		/// ���Ⴊ��ł���
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