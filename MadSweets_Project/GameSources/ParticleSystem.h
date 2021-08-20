#pragma once
#include"Bezier.h"

namespace basecross
{
	/// <summary>
	/// �p�[�e�B�N���Ɏg���l�̃C���^�[�t�F�[�X
	/// </summary>
	class I_ParticleValue
	{
	public:
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���l</returns>
		virtual float GetValueToTime(const float time) const = 0;
	};

	/// <summary>
	/// ���ԂɊ֌W�Ȃ��萔��Ԃ��l�N���X
	/// </summary>
	class ParticleValueConstant : public I_ParticleValue
	{
		/// <summary>
		/// �Ԃ��l
		/// </summary>
		float m_value = 0.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="value">�Ԃ��l</param>
		ParticleValueConstant(const float value);
		/// <summary>
		/// �Ԃ��l��ݒ肷��
		/// </summary>
		/// <param name="value">�Ԃ��l</param>
		void SetValue(const float value);
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���l</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// �x�W�F�Ȑ����g�����J�[�u�Ŏ��Ԃɑ΂���l��Ԃ��N���X
	/// </summary>
	class ParticleValueCurve : public I_ParticleValue
	{
		/// <summary>
		/// ���Ԃɑ΂���l���������x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezier;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="bezier">���Ԃɑ΂���l���������x�W�F�Ȑ�</param>
		ParticleValueCurve(const itbs::Math::BezierManager& bezier);
		/// <summary>
		/// �g�p����x�W�F�Ȑ���ݒ肷��
		/// </summary>
		/// <param name="bezier">���Ԃɑ΂���l���������x�W�F�Ȑ�</param>
		void SetCurve(const itbs::Math::BezierManager& bezier);
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���l</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// ��̒l�̊Ԃ������_���Œl��Ԃ��N���X
	/// </summary>
	class ParticleValueRandomBitweenConstants : public I_ParticleValue
	{
		/// <summary>
		/// �����_���ŏ��l
		/// </summary>
		float m_minValue = 0.0f;
		/// <summary>
		/// �����_���ő�l
		/// </summary>
		float m_maxValue = 0.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="minValue">�����_���ŏ��l</param>
		/// <param name="maxValue">�����_���ő�l</param>
		ParticleValueRandomBitweenConstants(const float minValue, const float maxValue);
		/// <summary>
		/// �����_���Ɏg���ŏ��l�ƍő�l��ݒ肷��
		/// </summary>
		/// <param name="minValue">�����_���Ɏg���ŏ��l</param>
		/// <param name="maxValue">�����_���Ɏg���ő�l</param>
		void SetValue(const float minValue, const float maxValue);
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���l</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// ��̃x�W�F�Ȑ����瓾���l�̊Ԃ������_���ɕԂ��N���X
	/// </summary>
	class ParticleValueRandomBitweenCurves : public I_ParticleValue
	{
		/// <summary>
		/// ��ڂ̃x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezier1;
		/// <summary>
		/// ��ڂ̃x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezier2;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="bezier1">��ڂ̃x�W�F�Ȑ�</param>
		/// <param name="bezier2">��ڂ̃x�W�F�Ȑ�</param>
		ParticleValueRandomBitweenCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);
		/// <summary>
		/// �g�p����x�W�F�Ȑ���ݒ肷��
		/// </summary>
		/// <param name="bezier1">��ڂ̃x�W�F�Ȑ�</param>
		/// <param name="bezier2">��ڂ̃x�W�F�Ȑ�</param>
		void SetCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���l</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// �p�[�e�B�N���Ɏg���x�N�g���̃C���^�[�t�F�[�X
	/// </summary>
	class I_ParticleVec3
	{
	public:
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		virtual Vec3 GetVec3ToTime(const float time) const = 0;
	};

	/// <summary>
	/// ���ԂɊ֌W�Ȃ��Œ�l��Ԃ��N���X
	/// </summary>
	class ParticleVec3Constant : public I_ParticleVec3
	{
		/// <summary>
		/// �Ԃ��x�N�g��
		/// </summary>
		Vec3 m_vec3;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="vec3">�Ԃ��Œ�l</param>
		ParticleVec3Constant(const Vec3& vec3);
		/// <summary>
		/// �Ԃ��Œ�l��ݒ肷��
		/// </summary>
		/// <param name="vec3">�Ԃ��Œ�l</param>
		void SetValue(const Vec3& vec3);
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		Vec3 GetVec3ToTime(const float time) const override;
	};

	/// <summary>
	/// ���Ԃɑ΂���l���������x�W�F�Ȑ����g���Ēl��Ԃ��N���X
	/// </summary>
	class ParticleVec3Curve : public I_ParticleVec3
	{
		/// <summary>
		/// X���̏����������x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezierX;
		/// <summary>
		/// Y���̏����������x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezierY;
		/// <summary>
		/// Z���̏����������x�W�F�Ȑ�
		/// </summary>
		itbs::Math::BezierManager m_bezierZ;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="bezierX">X���̏����������x�W�F�Ȑ�</param>
		/// <param name="bezierY">Y���̏����������x�W�F�Ȑ�</param>
		/// <param name="bezierZ">Z���̏����������x�W�F�Ȑ�</param>
		ParticleVec3Curve(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="bezierSize">X,Y,Z���Ŏg���x�W�F�Ȑ�</param>
		ParticleVec3Curve(const itbs::Math::BezierManager& bezierSize);

		/// <summary>
		/// ���Ԃɑ΂���x�N�g�����������x�W�F�Ȑ���ݒ肷��
		/// </summary>
		/// <param name="bezierX">X���̏����������x�W�F�Ȑ�</param>
		/// <param name="bezierY">Y���̏����������x�W�F�Ȑ�</param>
		/// <param name="bezierZ">Z���̏����������x�W�F�Ȑ�</param>
		void SetCurves(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);
		/// <summary>
		/// ���Ԃɑ΂���x�N�g�����������x�W�F�Ȑ���ݒ肷��
		/// </summary>
		/// <param name="bezierSize">X,Y,Z���̏����������x�W�F�Ȑ�</param>
		void SetCurve(const itbs::Math::BezierManager& bezierSize);

		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		Vec3 GetVec3ToTime(const float time) const override;
	};

	/// <summary>
	/// �p�[�e�B�N���Ŏg�p����F�̃C���^�[�t�F�[�X
	/// </summary>
	class I_ParticleColor
	{
	public:
		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		virtual Col4 GetColorToTime(const float time) const = 0;
	};

	/// <summary>
	/// ���ԂɊ֌W�Ȃ��Œ�l��Ԃ��N���X
	/// </summary>
	class ParticleColorConstant : public I_ParticleColor
	{
		/// <summary>
		/// �Ԃ��F
		/// </summary>
		Col4 m_color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="color">�Ԃ��F</param>
		ParticleColorConstant(const Col4& color);

		/// <summary>
		/// �Ԃ��F��ݒ肷��
		/// </summary>
		/// <param name="color">�Ԃ��F</param>
		void SetColor(const Col4& color);

		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		Col4 GetColorToTime(const float time) const override;
	};

	/// <summary>
	/// ��̐F�̊Ԃ������_���ɕԂ��N���X
	/// </summary>
	class ParticleColorRandomBitweenColors : public I_ParticleColor
	{
		/// <summary>
		/// ��ڂ̐F
		/// </summary>
		Col4 m_color1;
		/// <summary>
		/// ��ڂ̐F
		/// </summary>
		Col4 m_color2;

	public:

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="color1">��ڂ̐F</param>
		/// <param name="color2">��ڂ̐F</param>
		ParticleColorRandomBitweenColors(const Col4& color1, const Col4& color2);

		/// <summary>
		/// �g�p����F��ݒ肷��
		/// </summary>
		/// <param name="color1">��ڂ̐F</param>
		/// <param name="color2">��ڂ̐F</param>
		void SetColors(const Col4& color1, const Col4& color2);

		/// <summary>
		/// ���Ԃɑ΂���l��Ԃ�
		/// </summary>
		/// <param name="time">����</param>
		/// <returns>���Ԃɑ΂���x�N�g��</returns>
		Col4 GetColorToTime(const float time) const override;
	};

	/// <summary>
	/// ���Ԃɂ��p�[�e�B�N���̃o�[�X�g�Ɏg���f�[�^�\����
	/// </summary>
	class ParticleBurst
	{
		/// <summary>
		/// �o�[�X�g���J�n������
		/// </summary>
		bool m_isBurst = false;
		/// <summary>
		/// �o�[�X�g�J�n����
		/// </summary>
		float m_time = 0.0f;
		/// <summary>
		/// �o�[�X�g�����ۂɔ��������
		/// </summary>
		int m_count = 0;
		/// <summary>
		/// ����o�[�X�g���邩
		/// </summary>
		int m_cycles = 1;
		/// <summary>
		/// ����o�[�X�g������
		/// </summary>
		int m_cycleCount = 0;
		/// <summary>
		/// �o�[�X�g�C���^�[�o��
		/// </summary>
		float m_interval = 0.01f;
		/// <summary>
		/// �p�[�e�B�N������������m��
		/// </summary>
		float m_probabil = 1.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="time">���΂��鎞��</param>
		/// <param name="count">���΂����Ƃ��ɔ�������p�[�e�B�N����</param>
		/// <param name="cycles">����J��Ԃ���</param>
		/// <param name="interval">�N���AS���ɂǂꂮ�炢�̕b���J���邩</param>
		/// <param name="probabil">���o����m��</param>
		ParticleBurst(const float time, const int count, const int cycles, const float interval = 0.01f, const float probabil = 1.0f);

		/// <summary>
		/// �o�[�X�g�J�n�O�Ƀ��Z�b�g����
		/// </summary>
		/// <param name="duration">�p�[�e�B�N���Đ�����</param>
		void Reset(const float duration);
		/// <summary>
		/// �o�[�X�g�������ǂ������擾����
		/// </summary>
		/// <param name="time">���ݎ���</param>
		/// <returns>�o�[�X�g�������ǂ���</returns>
		bool IsBurst(const float time);
		/// <summary>
		/// ���p�[�e�B�N�����������邩�擾����
		/// </summary>
		/// <returns></returns>
		int GetCount() const;
		/// <summary>
		/// �m�����擾����
		/// </summary>
		/// <returns>��������m��</returns>
		float GetProbabil() const;
	};

	/// <summary>
	/// �p�[�e�B�N�������͈̓C���^�[�t�F�[�X
	/// </summary>
	class I_ParticleShape
	{
	public:
		/// <summary>
		/// �p�[�e�B�N�����������쐬����
		/// </summary>
		/// <param name="position">������</param>
		/// <param name="direction">�������̃x�N�g��</param>
		virtual void CreateEmission(Vec3& position,Vec3& direction) const = 0;
	};

	/// <summary>
	/// ���̃p�[�e�B�N�������͈̓N���X
	/// </summary>
	class ParticleShapeSphere : public I_ParticleShape
	{
		/// <summary>
		/// ���̔��a
		/// </summary>
		float m_radius = 1.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="radius">���̔��a</param>
		ParticleShapeSphere(const float radius = 1.0f);
		/// <summary>
		/// ���̔��a��ݒ肷��
		/// </summary>
		/// <param name="radius">���̔��a</param>
		void SetRadius(const float radius);
		/// <summary>
		/// �p�[�e�B�N�����������쐬����
		/// </summary>
		/// <param name="position">������</param>
		/// <param name="direction">�������̃x�N�g��</param>
		void CreateEmission(Vec3& position,Vec3& direction) const override;
	};

	/// <summary>
	/// �����̃p�[�e�B�N�������͈̓N���X
	/// </summary>
	class ParticleShapeHemisphere : public I_ParticleShape
	{
		/// <summary>
		/// �����̔��a
		/// </summary>
		float m_radius = 1.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="radius">�����̔��a</param>
		ParticleShapeHemisphere(const float radius = 1.0f);
		/// <summary>
		/// �����̔��a��ݒ肷��
		/// </summary>
		/// <param name="radius">�����̔��a</param>
		void SetRadius(const float radius);
		/// <summary>
		/// �p�[�e�B�N�����������쐬����
		/// </summary>
		/// <param name="position">������</param>
		/// <param name="direction">�������̃x�N�g��</param>
		void CreateEmission(Vec3& position, Vec3& direction) const override;
	};

	/// <summary>
	/// �~����̃p�[�e�B�N�������͈̓N���X
	/// </summary>
	class ParticleShapeCone : public I_ParticleShape
	{
		/// <summary>
		/// �~����̊p�x
		/// </summary>
		float m_angle;
		/// <summary>
		/// �~����̏�ʂ̔��a
		/// </summary>
		float m_radius;
		/// <summary>
		/// �~����̍���
		/// </summary>
		float m_length;

		/// <summary>
		/// �~����̒�ʂ̔��a
		/// </summary>
		float m_angleToRadius;
		/// <summary>
		/// ���[�J�����W
		/// </summary>
		Vec3 m_localPosition;
		/// <summary>
		/// ���[�J����]
		/// </summary>
		Quat m_localRotation;

		/// <summary>
		/// �~����̊p�x�����ʂ̔��a��ݒ肷��
		/// </summary>
		void SetAngleToRadius();

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="angle">�~����̊p�x</param>
		/// <param name="radius">�~����̏�ʂ̔��a</param>
		/// <param name="length">�~����̍���</param>
		ParticleShapeCone(const float angle = XMConvertToRadians(25), const float radius = 1.0f, const float length = 5.0f);

		/// <summary>
		/// �~����̊p�x��ݒ肷��
		/// </summary>
		/// <param name="angle">�~����̊p�x</param>
		void SetAngle(const float angle);
		/// <summary>
		/// �~����̏�ʂ̔��a�̐ݒ肷��
		/// </summary>
		/// <param name="radius">�~����̏�ʂ̔��a</param>
		void SetRadius(const float radius);
		/// <summary>
		/// �~����̍�����ݒ肷��
		/// </summary>
		/// <param name="length">�~����̍���</param>
		void SetLength(const float length);
		/// <summary>
		/// ���[�J�����W��ݒ肷��
		/// </summary>
		/// <param name="localPosition">���[�J�����W</param>
		void SetLocalPosition(const Vec3& localPosition);
		/// <summary>
		/// ���[�J����]��ݒ肷��
		/// </summary>
		/// <param name="localRotation">���[�J����]</param>
		void SetLocalRotation(const Vec3& localRotation);

		/// <summary>
		/// �p�[�e�B�N�����������쐬����
		/// </summary>
		/// <param name="position">������</param>
		/// <param name="direction">�������̃x�N�g��</param>
		void CreateEmission(Vec3& position, Vec3& direction) const override;
	};

	/// <summary>
	/// �p�[�e�B�N���Ǘ��R���|�[�l���g
	/// </summary>
	class ParticleSystem : public Component
	{
		/// <summary>
		/// �p�[�e�B�N���������̃f�[�^�\����
		/// </summary>
		struct StartSpriteData : public ParticleSprite
		{
			/// <summary>
			/// �d�͂̃X�P�[��
			/// </summary>
			float gravityScale;
			/// <summary>
			/// �J�����̌��������Ƃ�����]
			/// </summary>
			float rotation;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			StartSpriteData();
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="particleSprite">�p�[�e�B�N���X�v���C�g</param>
			/// <param name="gravityScale">�d�͂̃X�P�[��</param>
			/// <param name="rotation">�J�����̌��������Ƃ�����]</param>
			StartSpriteData(const ParticleSprite& particleSprite, const float gravityScale,const float rotation);
		};

		/// <summary>
		/// �p�[�e�B�N���Ǘ��p�f�[�^
		/// </summary>
		struct ParticleData
		{
			/// <summary>
			/// �p�[�e�B�N���̃|�C���^
			/// </summary>
			ex_weak_ptr<Particle> particle;
			/// <summary>
			/// �p�[�e�B�N���������̃f�[�^
			/// </summary>
			std::vector<StartSpriteData> startDatas;
			/// <summary>
			/// �p�[�e�B�N���ɑ΂��ė��ꂽ����
			/// </summary>
			float nowTime = 0.0f;
		};

		/// <summary>
		/// �f�t�H���g�Ńp�[�e�B�N���Ɏg���摜�̃L�[
		/// </summary>
		static const std::wstring DEFAULT_TEXTURE_KEY;

		/// <summary>
		/// �p�[�e�B�N���ɂ�����d�͂̕W��
		/// </summary>
		static constexpr float DEFAULT_GRAVITY_VALUE = 0.98f;

		/// <summary>
		/// �J�����|�C���^
		/// </summary>
		const ex_weak_ptr<Camera const> m_camera;

		/// <summary>
		/// �}���`�p�[�e�B�N���|�C���^
		/// </summary>
		ex_weak_ptr<MultiParticle> m_multiParticle;

		/// <summary>
		/// �p�[�e�B�N���Ǘ��p�z��
		/// </summary>
		std::vector<ParticleData> m_particleDatas;

		/// <summary>
		/// �p�[�e�B�N�����I�������ۂɃI�u�W�F�N�g���폜���邩
		/// </summary>
		bool m_isFinishedDestroy = false;
		/// <summary>
		/// �Đ����Ԃɑ΂��Ă̌��݂̎���
		/// </summary>
		float m_particleTimer = 0.0f;
		/// <summary>
		/// RateOverLifeTime�p�̎���
		/// </summary>
		float m_emissionTimer = 0.0f;
		/// <summary>
		/// �p�[�e�B�N���Đ�����
		/// </summary>
		float m_duration = 1.0f;
		/// <summary>
		/// ���[�v�����邩�ǂ���
		/// </summary>
		bool m_isLooping = true;
		/// <summary>
		/// �J�n���̃p�[�e�B�N������
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startLifeTime = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// �p�[�e�B�N�����o���̊J�n���x
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startSpeed = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// �p�[�e�B�N�����o���̃T�C�Y
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_startSize = std::make_shared<ParticleVec3Constant>(Vec3(1.0f));
		/// <summary>
		/// �p�[�e�B�N�����o���̃J�����̌����ɑ΂��Ẳ�]
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startRotation = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// �p�[�e�B�N�����o���̐F
		/// </summary>
		std::shared_ptr<I_ParticleColor> m_startColor = std::make_shared<ParticleColorConstant>(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		/// <summary>
		/// �p�[�e�B�N���ɂ�����d��
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_gravityScale = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// ���b�����p�[�e�B�N���𔭐������邩
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_rateOverTime = std::make_shared<ParticleValueConstant>(0);
		/// <summary>
		/// �p�[�e�B�N���o�[�X�g�p�̔z��
		/// </summary>
		std::vector<ParticleBurst> m_particleBursts;
		/// <summary>
		/// �p�[�e�B�N�������p�̌`
		/// </summary>
		std::shared_ptr<I_ParticleShape> m_particleShape = std::make_shared<ParticleShapeSphere>();
		/// <summary>
		/// ���Ԃɑ΂���p�[�e�B�N���ɉ�����
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_ForceOverLifeTime = std::make_shared<ParticleVec3Constant>(Vec3());
		/// <summary>
		/// ���Ԃɑ΂���T�C�Y�̔{��
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_sizeOverLifeTime = std::make_shared<ParticleVec3Constant>(Vec3(1.0f));
		/// <summary>
		/// �p�[�e�B�N���Ɏg���摜�̃L�[
		/// </summary>
		std::wstring m_textureKey = DEFAULT_TEXTURE_KEY;

		/// <summary>
		/// �p�[�e�B�N���쐬�֐�
		/// </summary>
		void CreateParticle();
		/// <summary>
		/// �p�[�e�B�N���X�V�֐�
		/// </summary>
		void UpdateParticle();

		/// <summary>
		/// �r���{�[�h�p�N�H�[�^�j�I�����쐬����
		/// </summary>
		/// <returns>�r���{�[�h�p�N�H�[�^�j�I��</returns>
		Quat CreateBillBoardQuat() const;
		/// <summary>
		/// �J�����̌��������Ƃ�����]��\���N�H�[�^�j�I�����쐬����
		/// </summary>
		/// <param name="rotation">��]</param>
		/// <returns>�J�����̌��������Ƃ�����]��\���N�H�[�^�j�I��</returns>
		Quat CreateRotationQuat(const float rotation) const;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		ParticleSystem(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// �p�[�e�B�N���Đ����Ԃ�ݒ肷��
		/// </summary>
		/// <param name="duration">�p�[�e�B�N���Đ�����</param>
		void SetDuration(const float duration);
		/// <summary>
		/// ���[�v���邩�ǂ�����ݒ肷��
		/// </summary>
		/// <param name="isLooping">���[�v���邩�ǂ���</param>
		void SetIsLooping(const bool isLooping);
		/// <summary>
		/// �J�n���̃p�[�e�B�N��������ݒ肷��
		/// </summary>
		/// <param name="startLifeTime">�p�[�e�B�N�������̒l</param>
		void SetStartLifeTime(const std::shared_ptr<I_ParticleValue>& startLifeTime);
		/// <summary>
		/// �J�n���̃p�[�e�B�N�����x��ݒ肷��
		/// </summary>
		/// <param name="startSpeed">�J�n���̃p�[�e�B�N�����x</param>
		void SetStartSpeed(const std::shared_ptr<I_ParticleValue>& startSpeed);
		/// <summary>
		/// �p�[�e�B�N�����o���̃T�C�Y��ݒ肷��
		/// </summary>
		/// <param name="startSize">�p�[�e�B�N�����o���̃T�C�Y</param>
		void SetStartSize(const std::shared_ptr<I_ParticleVec3>& startSize);
		/// <summary>
		/// �p�[�e�B�N�����o���̃J�����̌����ɑ΂��Ẳ�]��ݒ肷��
		/// </summary>
		/// <param name="startRotation">�p�[�e�B�N�����o���̃J�����̌����ɑ΂��Ẳ�]</param>
		void SetStartRotation(const std::shared_ptr<I_ParticleValue>& startRotation);
		/// <summary>
		/// �p�[�e�B�N�����o���̐F��ݒ肷��
		/// </summary>
		/// <param name="startColor">���o���̐F</param>
		void SetStartColor(const std::shared_ptr<I_ParticleColor>& startColor);
		/// <summary>
		/// �p�[�e�B�N���ɂ�����d�͂�ݒ肷��
		/// </summary>
		/// <param name="gravityScale">�p�[�e�B�N���ɂ�����d��</param>
		void SetGravityScale(const std::shared_ptr<I_ParticleValue>& gravityScale);
		/// <summary>
		/// �b������ɐ�������p�[�e�B�N������ݒ肷��
		/// </summary>
		/// <param name="rateOverTime">�b������ɐ�������p�[�e�B�N����</param>
		void SetRateOverTime(const std::shared_ptr<I_ParticleValue>& rateOverTime);
		/// <summary>
		/// �p�[�e�B�N���o�[�X�g����ǉ�����
		/// </summary>
		/// <param name="particleBurst">�p�[�e�B�N���o�[�X�g���</param>
		void AddEmissionBurst(const ParticleBurst& particleBurst);
		/// <summary>
		/// �p�[�e�B�N������o����͈͂̌`��ݒ肷��
		/// </summary>
		/// <param name="particleShape">�p�[�e�B�N������o����͈͂̌`</param>
		void SetShape(const std::shared_ptr<I_ParticleShape>& particleShape);
		/// <summary>
		/// �����ɑ΂��������͂�ݒ肷��
		/// </summary>
		/// <param name="forceOverLifeTime">�����ɑ΂���������</param>
		void SetForceOverLifeTime(const std::shared_ptr<I_ParticleVec3>& forceOverLifeTime);
		/// <summary>
		/// �����ɑ΂���T�C�Y�̔{����ݒ肷��
		/// </summary>
		/// <param name="sizeOverLifeTime">�����ɑ΂���T�C�Y�̔{��</param>
		void SetSizeOverLifeTime(const std::shared_ptr<I_ParticleVec3>& sizeOverLifeTime);
		/// <summary>
		/// �p�[�e�B�N���̉摜��ݒ肷��
		/// </summary>
		/// <param name="textureKey">�摜�̃L�[</param>
		void SetTextureKey(const std::wstring& textureKey);
		/// <summary>
		/// �p�[�e�B�N�����I�������ۂɃI�u�W�F�N�g���폜���邩��ݒ肷��
		/// </summary>
		/// <param name="isFinishedDestroy">�p�[�e�B�N�����I�������ۂɃI�u�W�F�N�g���폜���邩</param>
		void SetIsFinishedDestroy(const bool isFinishedDestroy);

		void OnPreCreate() override;

		void OnUpdate() override;
	};
}