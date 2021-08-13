#pragma once

namespace basecross
{
	/// <summary>
	/// �J�����p�R���|�[�l���g
	/// </summary>
	class CameraComponent : public Component
	{
		/// <summary>
		/// �J�����̃|�C���^
		/// </summary>
		ex_weak_ptr<Camera> m_camera;

		/// <summary>
		/// �J�����̎��_����ɑO�ɂ���
		/// </summary>
		void SetCameraAtForward();

		/// <summary>
		/// ���^�[�Q�b�g�ɂ���Ă��邩�ǂ���
		/// </summary>
		bool m_isTarget = false;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		CameraComponent(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate2() override;

		void OnEnable() override;

		void OnDisable() override;

	};
}