#pragma once
#include"PlayerProvider.h"
#include"AnimationHelper.h"
#include"PlayerObject.h"

namespace basecross
{
	/// <summary>
	/// �v���C���[��l�̃J�����̓�����S������R���|�[�l���g
	/// </summary>
	class PlayerFPSCameraMover : public Component
	{
		/// <summary>
		/// �J�����̌����p�̎q�I�u�W�F�N�g
		/// </summary>
		ex_weak_ptr<GameObject> m_lookAtObject;

		/// <summary>
		/// �X�e�[�W�̃J����
		/// </summary>
		ex_weak_ptr<Camera> m_targetCamera;

		ex_weak_ptr<Animator<PlayerAnimationMember, PlayerState>> m_playerAnimator;

		/// <summary>
		/// ���݂�Y��]
		/// </summary>
		float m_rotY = 0.0f;

		/// <summary>
		/// �ő�Y��]�p�x
		/// </summary>
		float m_maxRotY =  XM_PIDIV2;
		/// <summary>
		/// �ŏ�Y��]�p�x
		/// </summary>
		float m_minRotY = -XM_PIDIV2;

		Vec3 m_standPosition = Vec3(0, 1, 0);
		Vec3 m_crouchPosition = Vec3(0, 0, 0);
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		PlayerFPSCameraMover(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// �ő�Y��]�p�x��ݒ肷��
		/// </summary>
		/// <param name="rotY">Y��]�p�x</param>
		void SetMaxRotY(const float rotY);
		/// <summary>
		/// �ŏ�Y��]�p�x��ݒ肷��
		/// </summary>
		/// <param name="rotY">Y��]�p�x</param>
		void SetMinRotY(const float rotY);

		/// <summary>
		/// �ő�Y��]�p�x���擾����
		/// </summary>
		/// <returns>Y��]�p�x</returns>
		float GetMaxRotY() const;
		/// <summary>
		/// �ŏ�Y��]�p�x���擾����
		/// </summary>
		/// <returns>Y��]�p�x</returns>
		float GetMinRotY() const;

		void OnCreate() override;

		void OnUpdate() override;

		void OnUpdate2() override;
	};
}