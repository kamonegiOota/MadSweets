#pragma once
#include"Bezier.h"

namespace basecross
{

	class I_ParticleValue
	{
	public:
		virtual float GetValueToTime(const float time) const = 0;
	};

	class ParticleValueConstant : public I_ParticleValue
	{
		float m_value = 0.0f;

	public:
		ParticleValueConstant(const float value);

		void SetValue(const float value);

		float GetValueToTime(const float time) const override;
	};

	class ParticleValueCurve : public I_ParticleValue
	{
		itbs::Math::BezierManager m_bezier;

	public:
		ParticleValueCurve(const itbs::Math::BezierManager& bezier);

		void SetCurve(const itbs::Math::BezierManager& bezier);

		float GetValueToTime(const float time) const override;
	};

	class ParticleValueRandomBitweenConstants : public I_ParticleValue
	{
		float m_minValue = 0.0f;
		float m_maxValue = 0.0f;

	public:
		ParticleValueRandomBitweenConstants(const float minValue, const float maxValue);

		void SetValue(const float minValue, const float maxValue);

		float GetValueToTime(const float time) const override;
	};

	class ParticleValueRandomBitweenCurves : public I_ParticleValue
	{
		itbs::Math::BezierManager m_bezier1;
		itbs::Math::BezierManager m_bezier2;

	public:
		ParticleValueRandomBitweenCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);

		void SetCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);

		float GetValueToTime(const float time) const override;
	};

	class I_ParticleVec3
	{
	public:
		virtual Vec3 GetVec3ToTime(const float time) const = 0;
	};

	class ParticleVec3Constant : public I_ParticleVec3
	{
		Vec3 m_vec3;
	public:
		ParticleVec3Constant(const Vec3& vec3);

		void SetValue(const Vec3& vec3);

		Vec3 GetVec3ToTime(const float time) const override;
	};

	class ParticleVec3Curve : public I_ParticleVec3
	{
		itbs::Math::BezierManager m_bezierX;
		itbs::Math::BezierManager m_bezierY;
		itbs::Math::BezierManager m_bezierZ;

	public:
		ParticleVec3Curve(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);

		ParticleVec3Curve(const itbs::Math::BezierManager& bezierSize);

		void SetCurves(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);

		void SetCurve(const itbs::Math::BezierManager& bezierSize);

		Vec3 GetVec3ToTime(const float time) const override;
	};

	class I_ParticleColor
	{
	public:
		virtual Col4 GetColorToTime(const float time) const = 0;
	};

	class ParticleColorConstant : public I_ParticleColor
	{
		Col4 m_color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	public:
		ParticleColorConstant(const Col4& color);

		void SetColor(const Col4& color);

		Col4 GetColorToTime(const float time) const override;
	};

	class ParticleColorRandomBitweenColors : public I_ParticleColor
	{
		Col4 m_color1;
		Col4 m_color2;

	public:
		ParticleColorRandomBitweenColors(const Col4& color1, const Col4& color2);

		void SetColors(const Col4& color1, const Col4& color2);

		Col4 GetColorToTime(const float time) const override;
	};

	class ParticleBurst
	{
		bool m_isBurst = false;

		float m_time = 0.0f;

		int m_count = 0;

		int m_cycles = 1;

		int m_cycleCount = 0;

		float m_interval = 0.01f;

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

		void Reset(const float duration);

		bool IsBurst(const float time);

		int GetCount() const;

		float GetProbabil() const;
	};

	class I_ParticleShape
	{
	public:
		virtual void CreateEmissionPosition(Vec3& position,Vec3& direction) const = 0;
	};

	class ParticleShapeSphere : public I_ParticleShape
	{
		float m_radius = 1.0f;
	public:
		ParticleShapeSphere(const float radius = 1.0f);

		void SetRadius(const float radius);

		void CreateEmissionPosition(Vec3& position,Vec3& direction) const override;
	};

	class ParticleShapeHemisphere : public I_ParticleShape
	{
		float m_radius = 1.0f;
	public:
		ParticleShapeHemisphere(const float radius = 1.0f);

		void SetRadius(const float radius);

		void CreateEmissionPosition(Vec3& position, Vec3& direction) const override;
	};

	class ParticleShapeCone : public I_ParticleShape
	{
		float m_angle;
		float m_radius;
		float m_length;

		float m_angleToRadius;

		Vec3 m_localPosition;

		Quat m_localRotation;

		void SetAngleToRadius();
	public:
		ParticleShapeCone(const float angle = XMConvertToRadians(25), const float radius = 1.0f, const float length = 5.0f);

		void SetAngle(const float angle);

		void SetRadius(const float radius);

		void SetLength(const float length);

		void SetLocalPosition(const Vec3& localPosition);

		void SetLocalRotation(const Vec3& localRotation);

		void CreateEmissionPosition(Vec3& position, Vec3& direction) const override;
	};

	class ParticleSystem : public Component
	{
		struct StartSpriteData : public ParticleSprite
		{
			float gravityScale;
			float rotation;

			StartSpriteData();

			StartSpriteData(const ParticleSprite& particleSprite, const float gravityScale,const float rotation);
		};

		struct ParticleData
		{
			ex_weak_ptr<Particle> particle;
			std::vector<StartSpriteData> startDatas;
			float nowTime = 0.0f;
		};

		static const std::wstring DEFAULT_TEXTURE_KEY;

		static constexpr float DEFAULT_GRAVITY_VALUE = 0.98f;

		const ex_weak_ptr<Camera const> m_camera;

		ex_weak_ptr<MultiParticle> m_multiParticle;

		std::vector<ParticleData> m_particleDatas;
		/// <summary>
		/// �p�[�e�B�N�����I�������ۂɃI�u�W�F�N�g���폜���邩
		/// </summary>
		bool m_isFinishedDestroy = false;

		float m_particleTimer = 0.0f;

		float m_emissionTimer = 0.0f;

		float m_timer = 0.0f;

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

		std::wstring m_textureKey = DEFAULT_TEXTURE_KEY;

		void CreateParticle();

		void UpdateParticle();

		Quat CreateBillBoardQuat() const;

		Quat CreateRotationQuat(const float rotation) const;
	public:
		ParticleSystem(std::shared_ptr<GameObject>& owner);

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