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
		/// コンストラクタ
		/// </summary>
		/// <param name="time">発火する時間</param>
		/// <param name="count">発火したときに発生するパーティクル数</param>
		/// <param name="cycles">何回繰り返すか</param>
		/// <param name="interval">クリアS時にどれぐらいの秒数開けるか</param>
		/// <param name="probabil">放出する確率</param>
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
		/// パーティクルが終了した際にオブジェクトを削除するか
		/// </summary>
		bool m_isFinishedDestroy = false;

		float m_particleTimer = 0.0f;

		float m_emissionTimer = 0.0f;

		float m_timer = 0.0f;

		float m_duration = 1.0f;
		/// <summary>
		/// ループさせるかどうか
		/// </summary>
		bool m_isLooping = true;
		/// <summary>
		/// 開始時のパーティクル寿命
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startLifeTime = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// パーティクル放出時の開始速度
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startSpeed = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// パーティクル放出時のサイズ
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_startSize = std::make_shared<ParticleVec3Constant>(Vec3(1.0f));
		/// <summary>
		/// パーティクル放出時のカメラの向きに対しての回転
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startRotation = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// パーティクル放出時の色
		/// </summary>
		std::shared_ptr<I_ParticleColor> m_startColor = std::make_shared<ParticleColorConstant>(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		/// <summary>
		/// パーティクルにかかる重力
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_gravityScale = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// 毎秒いくつパーティクルを発生させるか
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_rateOverTime = std::make_shared<ParticleValueConstant>(0);
		/// <summary>
		/// パーティクルバースト用の配列
		/// </summary>
		std::vector<ParticleBurst> m_particleBursts;
		/// <summary>
		/// パーティクル生成用の形
		/// </summary>
		std::shared_ptr<I_ParticleShape> m_particleShape = std::make_shared<ParticleShapeSphere>();
		/// <summary>
		/// 時間に対するパーティクルに加わる力
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_ForceOverLifeTime = std::make_shared<ParticleVec3Constant>(Vec3());
		/// <summary>
		/// 時間に対するサイズの倍率
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
		/// ループするかどうかを設定する
		/// </summary>
		/// <param name="isLooping">ループするかどうか</param>
		void SetIsLooping(const bool isLooping);
		/// <summary>
		/// 開始時のパーティクル寿命を設定する
		/// </summary>
		/// <param name="startLifeTime">パーティクル寿命の値</param>
		void SetStartLifeTime(const std::shared_ptr<I_ParticleValue>& startLifeTime);
		/// <summary>
		/// 開始時のパーティクル速度を設定する
		/// </summary>
		/// <param name="startSpeed">開始時のパーティクル速度</param>
		void SetStartSpeed(const std::shared_ptr<I_ParticleValue>& startSpeed);
		/// <summary>
		/// パーティクル放出時のサイズを設定する
		/// </summary>
		/// <param name="startSize">パーティクル放出時のサイズ</param>
		void SetStartSize(const std::shared_ptr<I_ParticleVec3>& startSize);
		/// <summary>
		/// パーティクル放出時のカメラの向きに対しての回転を設定する
		/// </summary>
		/// <param name="startRotation">パーティクル放出時のカメラの向きに対しての回転</param>
		void SetStartRotation(const std::shared_ptr<I_ParticleValue>& startRotation);
		/// <summary>
		/// パーティクル放出時の色を設定する
		/// </summary>
		/// <param name="startColor">放出時の色</param>
		void SetStartColor(const std::shared_ptr<I_ParticleColor>& startColor);
		/// <summary>
		/// パーティクルにかかる重力を設定する
		/// </summary>
		/// <param name="gravityScale">パーティクルにかかる重力</param>
		void SetGravityScale(const std::shared_ptr<I_ParticleValue>& gravityScale);
		/// <summary>
		/// 秒あたりに生成するパーティクル数を設定する
		/// </summary>
		/// <param name="rateOverTime">秒あたりに生成するパーティクル数</param>
		void SetRateOverTime(const std::shared_ptr<I_ParticleValue>& rateOverTime);
		/// <summary>
		/// パーティクルバースト情報を追加する
		/// </summary>
		/// <param name="particleBurst">パーティクルバースト情報</param>
		void AddEmissionBurst(const ParticleBurst& particleBurst);
		/// <summary>
		/// パーティクルを放出する範囲の形を設定する
		/// </summary>
		/// <param name="particleShape">パーティクルを放出する範囲の形</param>
		void SetShape(const std::shared_ptr<I_ParticleShape>& particleShape);

		/// <summary>
		/// 寿命に対するサイズの倍率を設定する
		/// </summary>
		/// <param name="sizeOverLifeTime">寿命に対するサイズの倍率</param>
		void SetSizeOverLifeTime(const std::shared_ptr<I_ParticleVec3>& sizeOverLifeTime);
		/// <summary>
		/// パーティクルの画像を設定する
		/// </summary>
		/// <param name="textureKey">画像のキー</param>
		void SetTextureKey(const std::wstring& textureKey);
		/// <summary>
		/// パーティクルが終了した際にオブジェクトを削除するかを設定する
		/// </summary>
		/// <param name="isFinishedDestroy">パーティクルが終了した際にオブジェクトを削除するか</param>
		void SetIsFinishedDestroy(const bool isFinishedDestroy);

		void OnPreCreate() override;

		void OnUpdate() override;
	};
}