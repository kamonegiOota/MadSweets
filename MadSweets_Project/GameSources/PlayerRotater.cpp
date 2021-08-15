#include"PlayerRotater.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerRotater::PlayerRotater(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerRotater::Restrict(const float radian)
	{
		m_isRestrict = true;
		m_defaultRadian = transform->GetQuaternion().toRotVec().y;
		m_restrictRadian = radian;
	}

	void PlayerRotater::UnRestrict()
	{
		m_isRestrict = false;
	}

	void PlayerRotater::OnUpdate()
	{
		auto rotation = transform->GetQuaternion().toRotVec();

		auto rotationVector = PlayerInputer::GetCameraRotation();

		float rotY = rotation.y + rotationVector.x;

		if (m_isRestrict)
		{
			float halfRadian = m_restrictRadian * 0.5f;
			rotY = MyMath::Clamp(rotY, m_defaultRadian - halfRadian, m_defaultRadian + halfRadian);
		}

		transform->SetRotation(0, rotY, 0);

	}
}