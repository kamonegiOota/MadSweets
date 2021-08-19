#include"ParticleSystem.h"
#include"Random.h"
#include"MathHelper.h"

using itbs::Math::Random;
using itbs::Math::MyMath;
using itbs::Math::BezierManager;

namespace basecross
{
	// ParticleValueConstant -----------------------

	ParticleValueConstant::ParticleValueConstant(const float value) :
		m_value(value)
	{

	}

	void ParticleValueConstant::SetValue(const float value)
	{
		m_value = value;
	}

	float ParticleValueConstant::GetValueToTime(const float time) const
	{
		return m_value;
	}

	// ParticleValueRandomBitweenCurve -----------------------

	ParticleValueCurve::ParticleValueCurve(const BezierManager& bezier) :
		m_bezier(bezier)
	{

	}

	void ParticleValueCurve::SetCurve(const BezierManager& bezier)
	{
		m_bezier = bezier;
	}

	float ParticleValueCurve::GetValueToTime(const float time) const
	{
		return m_bezier.TimeToValue(time);
	}

	// ParticleValueRandomBitweenConstants -------------------

	ParticleValueRandomBitweenConstants::ParticleValueRandomBitweenConstants(const float minValue, const float maxValue) :
		m_minValue(minValue),
		m_maxValue(maxValue)
	{

	}

	void ParticleValueRandomBitweenConstants::SetValue(const float minValue, const float maxValue)
	{
		m_minValue = minValue;
		m_maxValue = maxValue;
	}

	float ParticleValueRandomBitweenConstants::GetValueToTime(const float time) const
	{
		return Random::Range(m_minValue, m_maxValue);
	}

	// ParticleValueBitweenCurves ------------------

	ParticleValueRandomBitweenCurves::ParticleValueRandomBitweenCurves(const BezierManager& bezier1, const BezierManager& bezier2) :
		m_bezier1(bezier1),
		m_bezier2(bezier2)
	{

	}

	void ParticleValueRandomBitweenCurves::SetCurves(const BezierManager& bezier1, const BezierManager& bezier2)
	{
		m_bezier1 = bezier1;
		m_bezier2 = bezier2;
	}

	float ParticleValueRandomBitweenCurves::GetValueToTime(const float time) const
	{
		float min = m_bezier1.TimeToValue(time);
		float max = m_bezier2.TimeToValue(time);

		if (min > max)
		{
			std::swap(min, max);
		}

		return Random::Range(min, max);
	}

	// ParticleVec3Constant ------------------------

	ParticleVec3Constant::ParticleVec3Constant(const Vec3& vec3) :
		m_vec3(vec3)
	{

	}

	void ParticleVec3Constant::SetValue(const Vec3& vec3)
	{
		m_vec3 = vec3;
	}

	Vec3 ParticleVec3Constant::GetVec3ToTime(const float time) const
	{
		return m_vec3;
	}

	// ParticleVec3Curve ---------------------------

	ParticleVec3Curve::ParticleVec3Curve(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ) :
		m_bezierX(bezierX),
		m_bezierY(bezierY),
		m_bezierZ(bezierZ)
	{

	}

	ParticleVec3Curve::ParticleVec3Curve(const itbs::Math::BezierManager& bezierSize) :
		ParticleVec3Curve(bezierSize, bezierSize, bezierSize)
	{

	}

	void ParticleVec3Curve::SetCurves(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ)
	{
		m_bezierX = bezierX;
		m_bezierY = bezierY;
		m_bezierZ = bezierZ;
	}

	void ParticleVec3Curve::SetCurve(const itbs::Math::BezierManager& bezierSize)
	{
		SetCurves(bezierSize, bezierSize, bezierSize);
	}

	Vec3 ParticleVec3Curve::GetVec3ToTime(const float time) const
	{
		return Vec3(m_bezierX.TimeToValue(time), m_bezierY.TimeToValue(time), m_bezierZ.TimeToValue(time));
	}

	// ParticleColorConstant -----------------------

	ParticleColorConstant::ParticleColorConstant(const Col4& color) :
		m_color(color)
	{

	}

	void ParticleColorConstant::SetColor(const Col4& color)
	{
		m_color = color;
	}

	Col4 ParticleColorConstant::GetColorToTime(const float time) const
	{
		return m_color;
	}

	// ParticleColorRandomBitweenColors ------------

	ParticleColorRandomBitweenColors::ParticleColorRandomBitweenColors(const Col4& color1, const Col4& color2) :
		m_color1(color1),
		m_color2(color2)
	{

	}

	void ParticleColorRandomBitweenColors::SetColors(const Col4& color1, const Col4& color2)
	{
		m_color1 = color1;
		m_color2 = color2;
	}

	Col4 ParticleColorRandomBitweenColors::GetColorToTime(const float time) const
	{
		float random = Random::Range(0.0f, 1.0f);

		return m_color1 + (m_color2 - m_color1) * random;
	}

	// ParticleBurst -------------------------------

	ParticleBurst::ParticleBurst(const float time, const int count, const int cycles, const float interval, const float probabil) :
		m_time(MyMath::Max(0.0f, time)),
		m_count(MyMath::Max(0, count)),
		m_cycles(MyMath::Max(1, cycles)),
		m_interval(MyMath::Max(0.01f, interval)),
		m_probabil(MyMath::Clamp(probabil, 0.0f, 1.0f))
	{
	}

	void ParticleBurst::Reset(const float duration)
	{
		m_isBurst = false;
		m_time = MyMath::Min(m_time, duration);
		m_cycleCount = 0;
	}

	bool ParticleBurst::IsBurst(const float time)
	{
		if (!m_isBurst)
		{
			if (time < m_time)
			{
				return false;
			}

			m_isBurst = true;

			m_cycleCount++;

			return true;
		}

		if (m_cycleCount >= m_cycles)
		{
			return false;
		}

		if (time < m_time + m_interval * m_cycleCount)
		{
			return false;
		}

		m_cycleCount++;

		return true;
	}

	int ParticleBurst::GetCount() const
	{
		return m_count;
	}

	float ParticleBurst::GetProbabil() const
	{
		return m_probabil;
	}

	// ParticleShapeSphere -------------------------

	ParticleShapeSphere::ParticleShapeSphere(const float radius) :
		m_radius(MyMath::Max(0.0f, radius))
	{

	}

	void ParticleShapeSphere::SetRadius(const float radius)
	{
		m_radius = MyMath::Max(radius, 0.0f);
	}

	void ParticleShapeSphere::CreateEmissionPosition(Vec3& position, Vec3& direction) const
	{
		direction = Vec3::Right();

		Quat quat;
		quat.rotationRollPitchYawFromVector(Vec3(Random::Range(0.0f, 360.0f), Random::Range(0.0f, 360.0f), Random::Range(0.0f, 360.0f)));

		direction = quat * direction;

		position = direction * Random::Range(0.0f, m_radius);
	}

	// ParticleShapeHemisphere ---------------------

	ParticleShapeHemisphere::ParticleShapeHemisphere(const float radius) :
		m_radius(MyMath::Max(radius, 0.0f))
	{

	}

	void ParticleShapeHemisphere::SetRadius(const float radius)
	{
		m_radius = MyMath::Max(radius, 0.0f);
	}

	void ParticleShapeHemisphere::CreateEmissionPosition(Vec3& position, Vec3& direction) const
	{
		direction = Vec3::Right();

		Quat quat;
		quat.rotationRollPitchYawFromVector(Vec3(Random::Range(0.0f, 360.0f), Random::Range(0.0f, 360.0f), Random::Range(0.0f, 360.0f)));

		direction = quat * direction;

		if (direction.y < 0)
		{
			direction.y *= -1;
		}

		position = direction * Random::Range(0.0f, m_radius);
	}

	// ParticleShapeCone ---------------------------

	ParticleShapeCone::ParticleShapeCone(const float angle, const float radius, const float length) :
		m_angle(MyMath::Clamp(angle, 0.0f, XM_PIDIV2)),
		m_radius(MyMath::Max(radius, 0.001f)),
		m_length(MyMath::Max(length, 0.0f))
	{
		SetAngleToRadius();
	}

	void ParticleShapeCone::SetAngleToRadius()
	{
		if (m_angle != XM_PIDIV2)
		{
			m_angleToRadius = std::tanf(m_angle) * m_length;
		}
	}

	void ParticleShapeCone::SetAngle(const float angle)
	{
		m_angle = MyMath::Clamp(angle, 0.0f, XM_PIDIV2);
		SetAngleToRadius();
	}

	void ParticleShapeCone::SetRadius(const float radius)
	{
		m_radius = MyMath::Max(radius, 0.001f);
	}

	void ParticleShapeCone::SetLength(const float length)
	{
		m_length = MyMath::Max(length, 0.0f);
		SetAngleToRadius();
	}

	void ParticleShapeCone::SetLocalPosition(const Vec3& localPosition)
	{
		m_localPosition = localPosition;
	}

	void ParticleShapeCone::SetLocalRotation(const Vec3& localRotation)
	{
		m_localRotation.rotationRollPitchYawFromVector(localRotation);
	}

	void ParticleShapeCone::CreateEmissionPosition(Vec3& position, Vec3& direction) const
	{
		Vec3 circleDirection = Vec3::Right();

		Quat quat;
		quat.rotationRollPitchYawFromVector(Vec3(0.0f, Random::Range(0.0f, 360.0f), 0.0f));

		circleDirection = quat * Vec3::Right();

		float randomRadius = Random::Range(0.0f, m_radius);
		position = circleDirection * randomRadius;

		if (m_angle == XM_PIDIV2)
		{
			direction = circleDirection;

			return;
		}

		Vec3 bottomPosition = circleDirection * (randomRadius * (m_radius + m_angleToRadius) / m_radius) + Vec3(0, m_length, 0);

		direction = bottomPosition - position;
		direction.normalize();

		position += direction * Random::Range(0.0f, m_length);

		position = m_localRotation * position;
		direction = m_localRotation * direction;

		position += m_localPosition;

		return;
	}

	// StartSpriteData -----------------------------

	ParticleSystem::StartSpriteData::StartSpriteData() :
		StartSpriteData(ParticleSprite(), 0.0f, 0.0f)
	{

	}

	ParticleSystem::StartSpriteData::StartSpriteData(const ParticleSprite& sprite, const float gravityScale,
		const float rotation) :
		ParticleSprite(sprite),
		gravityScale(gravityScale),
		rotation(rotation)
	{

	}
	
	// ParticleSystem ------------------------------

	const std::wstring ParticleSystem::DEFAULT_TEXTURE_KEY = L"_PARTICLE_DEFAULT_TEXTURE_KEY";

	ParticleSystem::ParticleSystem(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_camera(GetStage()->GetView()->GetTargetCamera())
	{
		if (!App::GetApp()->CheckResourceKey(DEFAULT_TEXTURE_KEY))
		{
			App::GetApp()->RegisterTexture(DEFAULT_TEXTURE_KEY, App::GetApp()->GetDataDirWString() + L"Textures/Particle_Default.png");
		}
	}

	void ParticleSystem::CreateParticle()
	{
		if (m_particleTimer >= m_duration)
		{
			if (!m_isLooping)
			{
				m_particleTimer = m_duration;
				return;
			}

			m_particleTimer -= m_duration;

			for (auto& particleBurst : m_particleBursts)
			{
				particleBurst.Reset(m_duration);
			}
		}

		float time = m_particleTimer / m_duration;

		int createCount = 0;

		m_particleTimer += App::GetApp()->GetElapsedTime();
		m_emissionTimer += App::GetApp()->GetElapsedTime();

		float rateOverTime = m_rateOverTime->GetValueToTime(time);

		if (rateOverTime != 0 && m_emissionTimer >= 1.0f / rateOverTime)
		{
			m_emissionTimer -= 1.0f / rateOverTime;

			createCount++;
		}

		for (auto& particleBurst : m_particleBursts)
		{
			if (particleBurst.IsBurst(m_particleTimer))
			{
				int count = particleBurst.GetCount();

				for (int i = 0; i < count; i++)
				{
					if (Random::Probability(particleBurst.GetProbabil()))
					{
						createCount++;
					}
				}
			}
		}

		auto particle = m_multiParticle->InsertParticle(createCount, Particle::DrawOption::Normal);

		particle->SetTextureResource(m_textureKey);
		particle->SetEmitterPos(transform->GetWorldPosition());
		particle->SetMaxTime(m_startLifeTime->GetValueToTime(time));
		
		Vec3 emissionPosition;
		Vec3 direction;

		m_particleDatas.push_back(ParticleData());

		auto& particleData = m_particleDatas.back();
		particleData.particle = particle;

		auto& particleSprites = particle->GetParticleSpriteVec();

		particleData.startDatas.resize(particleSprites.size());

		for (int i = 0; i < particleSprites.size(); i++)
		{
			auto& sprite = particleSprites[i];

			m_particleShape->CreateEmissionPosition(emissionPosition, direction);
			
			sprite.m_LocalPos = emissionPosition;
			sprite.m_LocalScale = m_startSize->GetVec3ToTime(time);
			//sprite.m_Color = m_startColor->GetColorToTime(time);

			Quat quat = CreateBillBoardQuat();

			float rotation = m_startRotation->GetValueToTime(time);

			sprite.m_LocalQt = quat * CreateRotationQuat(rotation);
			
			sprite.m_Velocity = direction * m_startSpeed->GetValueToTime(time);

			particleData.startDatas[i] = StartSpriteData(sprite, m_gravityScale->GetValueToTime(time), rotation);
		}
	}

	void ParticleSystem::UpdateParticle()
	{
		auto it = m_particleDatas.begin();

		while (it != m_particleDatas.end())
		{
			auto& particle = it->particle;

			if (!particle || !particle->IsActive())
			{
				it = m_particleDatas.erase(it);

				continue;
			}

			auto& particleSprites = particle->GetParticleSpriteVec();
			auto& startDatas = it->startDatas;

			it->nowTime += App::GetApp()->GetElapsedTime();

			if (it->nowTime > particle->GetMaxTime())
			{
				it->nowTime = particle->GetMaxTime();
			}

			for (int i = 0; i < particleSprites.size(); i++)
			{
				auto& sprite = particleSprites[i];

				if (!sprite.m_Active)
				{
					continue;
				}


				auto maxTime = particle->GetMaxTime();

				sprite.m_Velocity -= Vec3(0, DEFAULT_GRAVITY_VALUE, 0) * startDatas[i].gravityScale;

				sprite.m_LocalScale = startDatas[i].m_LocalScale;

				sprite.m_LocalQt = CreateBillBoardQuat() * CreateRotationQuat(startDatas[i].rotation);

				auto sizeOverLifeTime = m_sizeOverLifeTime->GetVec3ToTime(it->nowTime / particle->GetMaxTime());
				sprite.m_LocalScale.x *= sizeOverLifeTime.x;
				sprite.m_LocalScale.y *= sizeOverLifeTime.y;
			}

			it++;
		}
	}

	Quat ParticleSystem::CreateBillBoardQuat() const
	{
		Quat quat;
		Mat4x4 rotMatrix;
		auto cameraForward = m_camera->GetAt() - m_camera->GetEye();

		Vec3 DefaultUp = Vec2(cameraForward.x, cameraForward.z).length() < 0.1f ? Vec3(0, 0, 1.0f) : Vec3(0, 1.0f, 0);
		cameraForward.normalize();
		rotMatrix = XMMatrixLookAtLH(Vec3(), cameraForward, DefaultUp);
		rotMatrix.inverse();
		quat = rotMatrix.quatInMatrix();
		quat.normalize();

		return quat;
	}

	Quat ParticleSystem::CreateRotationQuat(const float rotation) const
	{
		auto cameraForward = m_camera->GetAt() - m_camera->GetEye();
		cameraForward.normalize();

		Quat rot = Quat::Identity();
		rot.rotation(cameraForward, rotation);

		return rot;
	}

	void ParticleSystem::SetDuration(const float duration)
	{
		m_duration = MyMath::Max(duration, 0.05f);

		for (auto& particleBurst : m_particleBursts)
		{
			particleBurst.Reset(m_duration);
		}
	}

	void ParticleSystem::SetIsLooping(const bool isLooping)
	{
		m_isLooping = isLooping;
	}

	void ParticleSystem::SetStartLifeTime(const std::shared_ptr<I_ParticleValue>& startLifeTime)
	{
		m_startLifeTime = startLifeTime;
	}

	void ParticleSystem::SetStartSpeed(const std::shared_ptr<I_ParticleValue>& startSpeed)
	{
		m_startSpeed = startSpeed;
	}

	void ParticleSystem::SetStartSize(const std::shared_ptr<I_ParticleVec3>& startSize)
	{
		m_startSize = startSize;
	}

	void ParticleSystem::SetStartRotation(const std::shared_ptr<I_ParticleValue>& startRotation)
	{
		m_startRotation = startRotation;
	}

	void ParticleSystem::SetStartColor(const std::shared_ptr<I_ParticleColor>& startColor)
	{
		m_startColor = startColor;
	}

	void ParticleSystem::SetGravityScale(const std::shared_ptr<I_ParticleValue>& gravityScale)
	{
		m_gravityScale = gravityScale;
	}

	void ParticleSystem::SetRateOverTime(const std::shared_ptr<I_ParticleValue>& rateOverTime)
	{
		m_rateOverTime = rateOverTime;
	}

	void ParticleSystem::AddEmissionBurst(const ParticleBurst& particleBurst)
	{
		m_particleBursts.push_back(particleBurst);
		m_particleBursts.back().Reset(m_duration);
	}

	void ParticleSystem::SetShape(const std::shared_ptr<I_ParticleShape>& particleShape)
	{
		m_particleShape = particleShape;
	}

	void ParticleSystem::SetSizeOverLifeTime(const std::shared_ptr<I_ParticleVec3>& sizeOverLifeTime)
	{
		m_sizeOverLifeTime = sizeOverLifeTime;
	}

	void ParticleSystem::SetTextureKey(const std::wstring& textureKey)
	{
		m_textureKey = textureKey;
	}

	void ParticleSystem::OnPreCreate()
	{
		Component::OnPreCreate();

		m_multiParticle = GetStage()->AddGameObject<MultiParticle>();

		SetStartLifeTime(std::make_shared<ParticleValueConstant>(1.0f));

		BezierManager bezier = BezierManager(5.0f);
		bezier.AddAnchorPoint(itbs::Math::BezierAnchorPoint(0.5f, 0.0f));
		bezier.AddAnchorPoint(itbs::Math::BezierAnchorPoint(1.0f, 5.0f));

		//Ç±ÇÃèëÇ´ï˚ÇæÇ∆ÉãÅ[ÉvÇ∑ÇÈÇ‹Ç≈ÇÃéûä‘Ç…ëŒÇµÇƒÇªÇÍÇ0Å`1Ç…ÇµÇΩÇ∆Ç´Ç…
		//0 ÇÃéûÇ… 5, 0.5 ÇÃéûÇ… 0, 1 ÇÃéûÇ…5Ç…Ç»ÇÈÇÊÇ§Ç…Ç»Ç¡ÇƒÇÈ
		//SetStartSpeed(std::make_shared<ParticleValueCurve>(bezier));

		SetStartSpeed(std::make_shared<ParticleValueConstant>(10));

		SetStartSize(std::make_shared<ParticleVec3Constant>(Vec3(1.0f)));

		SetStartRotation(std::make_shared<ParticleValueRandomBitweenConstants>(0.0f, XM_2PI));

		SetStartColor(std::make_shared<ParticleColorConstant>(Col4(1, 1, 0, 1)));

		//Ç±ÇÍÇ™ñàïbâΩå¬èoÇ∑Ç©
		SetRateOverTime(std::make_shared<ParticleValueConstant>(10.0f));

		//AddEmissionBurst(ParticleBurst(0.0f, 20, 10,1.0f,1.0f));
		auto shape = std::make_shared<ParticleShapeCone>(XM_PIDIV4, 0.0f);
		//shape->SetLocalRotation(Vec3(XM_PIDIV2, 0, 0));
		SetShape(shape);

		SetGravityScale(std::make_shared<ParticleValueConstant>(0.0f));
		SetTextureKey(L"HpDraw_Tx");

		bezier = BezierManager(1.0f);
		bezier.AddAnchorPoint(itbs::Math::BezierAnchorPoint(1.0f, 0.0f));

		SetSizeOverLifeTime(std::make_shared<ParticleVec3Curve>(bezier));

		SetDuration(10.0f);
	}

	void ParticleSystem::OnUpdate()
	{
		if (m_particleTimer >= m_duration && !m_isLooping)
		{
			bool isFinished = true;
			for (auto& particleData : m_particleDatas)
			{
				if (!particleData.particle->IsActive())
				{
					isFinished = false;
					break;
				}
			}

			if (isFinished)
			{
				GetGameObject()->Destroy();
				return;
			}
		}

		UpdateParticle();

		CreateParticle();
	}
}