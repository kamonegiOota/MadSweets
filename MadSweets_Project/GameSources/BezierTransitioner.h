#pragma once
#include"Bezier.h"
#include<functional>

using namespace itbs::Math;

namespace basecross
{
	/// <summary>
	/// �O���t�f�[�^��p���A�o�^���ꂽ�֐��ɑJ�ڃf�[�^������R���|�[�l���g
	/// </summary>
	class BezierTransitioner : public Component
	{
		/// <summary>
		/// �o�^�֐��^
		/// </summary>
		using func_type = std::function<void(const float)>;

		/// <summary>
		/// �ĂԊ֐��Ƃ��̃f�[�^�}�l�[�W���[�̃y�A
		/// </summary>
		struct FunctionPointPair
		{
			/// <summary>
			/// �֐��f�[�^
			/// </summary>
			func_type function;
			/// <summary>
			/// �x�W�F�f�[�^�}�l�[�W���[
			/// </summary>
			BezierManager pointManager;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="function">�֐��f�[�^</param>
			/// <param name="manager">�x�W�F�f�[�^�}�l�[�W���[</param>
			FunctionPointPair(func_type function, const BezierManager& manager);
		};

		/// <summary>
		/// �Ǘ��y�A�z��
		/// </summary>
		std::vector<FunctionPointPair> m_pointManagers;

		/// <summary>
		/// �Đ������ǂ���
		/// </summary>
		bool m_isPlaying = true;
		
		/// <summary>
		/// ���݂̍Đ��ʒu����
		/// </summary>
		float m_time = 0;
		/// <summary>
		/// ���[�v�J�n����
		/// </summary>
		float m_loopTime = 0;

		/// <summary>
		/// ���[�v���邩�ǂ���
		/// </summary>
		bool m_isLoop = false;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		BezierTransitioner(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// �Ǘ�����x�W�F�f�[�^�}�l�[�W���[��o�^����
		/// </summary>
		/// <param name="function">�Ă΂��֐�</param>
		/// <param name="manager">�x�W�F�f�[�^�}�l�[�W���[</param>
		void AddManager(func_type function, const BezierManager& manager);

		/// <summary>
		/// �Đ��J�n
		/// </summary>
		void Play();

		/// <summary>
		/// �Đ���~
		/// </summary>
		void Stop();

		/// <summary>
		/// ���Ԃ��΂�
		/// </summary>
		/// <param name="skipTime">��΂�����</param>
		void Skip(const float skipTime);

		/// <summary>
		/// �C�ӎ��ԂɈړ�
		/// </summary>
		/// <param name="time">����</param>
		void Move(const float time);

		/// <summary>
		/// ���߂Ɉړ�
		/// </summary>
		void MoveStart();

		/// <summary>
		/// �I���ʒu�܂ňړ�
		/// </summary>
		void MoveEnd();

		/// <summary>
		/// ���[�v���邩�ǂ�����ݒ肷��
		/// </summary>
		/// <param name="isLoop">���[�v���邩�ǂ���</param>
		void SetIsLoop(const bool isLoop);

		/// <summary>
		/// �������֐�
		/// </summary>
		void OnCreate() override {}

		/// <summary>
		/// �X�V�֐�
		/// </summary>
		void OnUpdate() override;

		/// <summary>
		/// �`��֐�
		/// </summary>
		void OnDraw() override {}
	};
}