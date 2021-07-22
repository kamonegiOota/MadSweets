#include"SpringArmComponent.h"

namespace basecross
{
	SpringArmComponent::SpringArmComponent(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void SpringArmComponent::SetArmRange(const float armRange)
	{
		m_armRange = armRange;
	}

	float SpringArmComponent::GetArmRange() const
	{
		return m_armRange;
	}

	void SpringArmComponent::AddHitTag(const std::wstring& hitTag)
	{
		m_hitTags.push_back(hitTag);
	}

	void SpringArmComponent::RemoveHitTag(const std::wstring& hitTag)
	{
		auto it = std::find(m_hitTags.begin(), m_hitTags.end(), hitTag);

		if (it != m_hitTags.end())
		{
			m_hitTags.erase(it);
		}
	}

	void SpringArmComponent::SetChildObject(const std::shared_ptr<GameObject>& childObject)
	{
		m_childObject = childObject;
		m_childTransform = childObject->GetComponent<Transform>();

		m_direction = m_childTransform->GetPosition();
		m_direction.normalize();
	}


	void SpringArmComponent::OnUpdate()
	{
		if (!m_childObject)
		{
			return;
		}

		auto startPosition = transform->GetWorldPosition();
		auto pos = m_childTransform->GetWorldPosition();
		auto rayDirection = m_childTransform->GetWorldPosition() - startPosition;

		if (rayDirection.lengthSqr() == 0)
		{
			return;
		}

		rayDirection.normalize();

		RayHitData maxHitData;
		maxHitData.length = m_armRange;
		maxHitData.point = startPosition + rayDirection * m_armRange;

		for (auto& object : GetStage()->GetGameObjectVec())
		{
			auto collision = object->GetComponent<Collision>(false);

			if (!collision)
			{
				continue;
			}

			bool isHitTagFind = false;

			for (auto& hitTag : m_hitTags)
			{
				if (object->FindTag(hitTag))
				{
					isHitTagFind = true;
					break;
				}
			}

			if (!isHitTagFind)
			{
				continue;
			}

			RayHitData hitData;
			bool isHit = collision->IsRayHit(startPosition, rayDirection, hitData);

			if (!isHit)
			{
				continue;
			}

			if (hitData.length < maxHitData.length)
			{
				maxHitData = hitData;
			}
		}
		
		m_childTransform->SetPosition(m_direction * maxHitData.length);
	}
}