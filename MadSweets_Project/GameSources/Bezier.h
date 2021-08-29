#pragma once
#include<map>

namespace itbs
{
	namespace Math
	{
		/// <summary>
		/// �x�W�F�O���t��̓_��\���\����
		/// </summary>
		struct BezierPoint
		{
			/// <summary>
			/// ���� (�O���t���X���W)
			/// </summary>
			float time;
			/// <summary>
			/// �l (�O���t���Y���W)
			/// </summary>
			float value;

		public:
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			BezierPoint();
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="time">����</param>
			/// <param name="value">�l</param>
			BezierPoint(const float time, const float value);

			bool operator==(const BezierPoint& other) const;
			bool operator!=(const BezierPoint& other) const;

			BezierPoint operator+(const BezierPoint& other) const;
		};

		/// <summary>
		/// �x�W�F�O���t�̃A���J�[�|�C���g��\���\����
		/// </summary>
		struct BezierAnchorPoint
		{
			/// <summary>
			/// �A���J�[�|�C���g���̂̍��W
			/// </summary>
			BezierPoint point;
			/// <summary>
			/// �����̃n���h���̍��W (���g�Ƃ̑��΍��W)
			/// </summary>
			BezierPoint leftHandle;
			/// <summary>
			/// �E���̃n���h���̍��W (���g�Ƃ̑��΍��W)
			/// </summary>
			BezierPoint rightHandle;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="point">�A���J�[�|�C���g���̂̍��W</param>
			BezierAnchorPoint(const BezierPoint& point);

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="time">�A���J�[�|�C���g���̂̎��� (�O���t���X���W)</param>
			/// <param name="value">�A���J�[�|�C���g���̂̒l (�O���t��̍��W)</param>
			BezierAnchorPoint(const float time, const float value);

			/// <summary>
			/// ���n���h�����L�����ǂ���
			/// </summary>
			/// <returns>�L���Ȃ�true</returns>
			bool IsLeftValid() const;

			/// <summary>
			/// �E�n���h�����L�����ǂ���
			/// </summary>
			/// <returns>�L���Ȃ�true</returns>
			bool IsRightVaild() const;

			/// <summary>
			/// ���̃n���h�����W���A�n���h���̒����Ɗp�x���������� (�J�n�n�_�͍��A��]�͔����v���)
			/// </summary>
			/// <param name="length">�n���h���̒���</param>
			/// <param name="radian">�n���h���̊p�x</param>
			void SetLeftHandleFromRadian(const float length, const float radian);

			/// <summary>
			/// �E�̃n���h�����W���A�n���h���̒����Ɗp�x���������� (�J�n�n�_�͉E�A��]�͎��v���)
			/// </summary>
			/// <param name="length">�n���h���̒���</param>
			/// <param name="radian">�n���h���̊p�x</param>
			void SetRightHandleFromRadian(const float length, const float radian);

			/// <summary>
			///	���E�ɒ���1�A�p�x�����̃n���h�����쐬����
			/// </summary>
			void SetDefaultHandle();

			/// <summary>
			/// ���̃n���h�����폜����
			/// </summary>
			void DeleteLeftHandle();
			/// <summary>
			/// �E�̃n���h�����폜����
			/// </summary>
			void DeleteRightHandle();
		};

		/// <summary>
		/// �x�W�F�O���t�f�[�^�}�l�[�W���[�N���X
		/// </summary>
		class BezierManager
		{
			/// <summary>
			/// �A���J�[�|�C���g�f�[�^�z��
			/// </summary>
			std::map<float, BezierAnchorPoint> m_anchorPoints;

			/// <summary>
			/// �_����̏ꍇ�̒l(y�l)�̌v�Z
			/// </summary>
			/// <param name="time">���� (x�l)</param>
			/// <param name="p1">�_�P</param>
			/// <param name="p2">�_�Q</param>
			/// <returns>�l (y�l)</returns>
			float GetTime(const float time,const BezierPoint& p1, const BezierPoint& p2) const;
			/// <summary>
			/// �_���O�̏ꍇ�̒l(y�l)�̌v�Z
			/// </summary>
			/// <param name="time">���� (x�l)</param>
			/// <param name="p1">�_�P</param>
			/// <param name="p2">�_�Q</param>
			/// <param name="p3">�_�R</param>
			/// <returns>�l (y�l)</returns>
			float GetTime(const float time, const BezierPoint& p1, const BezierPoint& p2, const BezierPoint& p3) const;
			/// <summary>
			/// �_���l�̏ꍇ�̒l(y�l)�̌v�Z
			/// </summary>
			/// <param name="time">���� (x�l)</param>
			/// <param name="p1">�_�P</param>
			/// <param name="p2">�_�Q</param>
			/// <param name="p3">�_�R</param>
			/// <param name="p4">�_�S</param>
			/// <returns>�l (y�l)</returns>
			float GetTime(const float time, const BezierPoint& p1, const BezierPoint& p2, const BezierPoint& p3, const BezierPoint& p4) const;
		public:
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="startValue">�����_(time = 0.0f)�̒l</param>
			BezierManager(const float startValue);

			/// <summary>
			/// �A���J�[�|�C���g�̒ǉ�
			/// </summary>
			/// <param name="bezierPoint">�A���J�[�|�C���g���̂̍��W</param>
			/// <returns>�ǉ������A���J�[�|�C���g�̎Q��</returns>
			BezierAnchorPoint& AddAnchorPoint(const BezierPoint& bezierPoint);
			/// <summary>
			/// �A���J�[�|�C���g�̒ǉ�
			/// </summary>
			/// <param name="bezierPoint">�A���J�[�|�C���g�̃f�[�^</param>
			/// <returns>�ǉ������A���J�[�|�C���g�̎Q��</returns>
			BezierAnchorPoint& AddAnchorPoint(const BezierAnchorPoint& bezierPoint);
			/// <summary>
			/// �A���J�[�|�C���g�̒ǉ�
			/// </summary>
			/// <param name="time">�A���J�[�|�C���g���̂̎��� (x�l)</param>
			/// <param name="value">�A���J�[�|�C���g���̂̒l (y�l)</param>
			/// <returns>�ǉ������A���J�[�|�C���g�̎Q��</returns>
			BezierAnchorPoint& AddAnchorPoint(const float time, const float value);

			/// <summary>
			/// �����_(time = 0.0f)�̃A���J�[�|�C���g�̎擾
			/// </summary>
			/// <returns>�����_�̎Q��</returns>
			BezierAnchorPoint& GetZeroAnchorPoint();

			/// <summary>
			/// �Ō�̃A���J�[�|�C���g��time���擾����
			/// </summary>
			/// <returns>�Ō�̃A���J�[�|�C���g��time</returns>
			float GetLastPointTime() const;

			/// <summary>
			/// ���Ԃ���O���t�f�[�^���value���擾����
			/// </summary>
			/// <param name="time">�擾���鎞��</param>
			/// <returns>���ԂɑΉ������l</returns>
			float TimeToValue(const float time) const;
		};
	}

	namespace Utility
	{
		class TimeLineFloat
		{
			Math::BezierManager m_bezier;

			float m_nowTime = 0.0f;
			float m_maxTime = 1.0f;

			bool m_isReverse = false;

		public:
			TimeLineFloat(const Math::BezierManager& bezier, const float maxTime);

			void SetNowTime(const float nowTime);
			void SetMaxTime(const float maxTime);
			void SetBezierManager(const Math::BezierManager& bezier);

			void SetIsReverse(const bool isReverse);

			void AddTime(const float time);

			float GetValue() const;

			bool IsFinish() const;

			void TimeReset();
		};
	}
}