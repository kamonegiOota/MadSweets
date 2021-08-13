#pragma once

namespace basecross
{
	/// <summary>
	/// �J�����̉�]��S������R���|�[�l���g
	/// </summary>
	class CameraRotater : public Component
	{
		/// <summary>
		/// �ŏ��̉�]�̊p�x
		/// </summary>
		float m_minRotX = -XM_PIDIV2;
		/// <summary>
		/// �ő�̉�]�̊p�x
		/// </summary>
		float m_maxRotX = XM_PIDIV2;

		float m_rotX = 0.0f;
	public:
		CameraRotater(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// X���̉�]�̍ő�l��ݒ肷��
		/// </summary>
		/// <param name="maxRotX">X����]�̍ő�l</param>
		void SetMaxRotX(const float maxRotX);
		/// <summary>
		/// X���̉�]�̍ő�l���擾����
		/// </summary>
		/// <returns>X���̉�]�̍ő�l</returns>
		float GetMaxRotX() const;

		/// <summary>
		/// X���̍ŏ��̉�]�l��ݒ肷��
		/// </summary>
		/// <param name="minRotX">X���̍ŏ��̉�]�l</param>
		void SetMinRotX(const float minRotX);
		/// <summary>
		/// X���̉�]�̍ŏ��l���擾����
		/// </summary>
		/// <returns>X���̉�]�̍ŏ��l</returns>
		float GetMinRotX() const;

		void OnUpdate() override;
	};
}