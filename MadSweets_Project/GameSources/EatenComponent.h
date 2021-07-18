#pragma once

namespace basecross
{
	struct EatenData
	{
		float weightValue;

		EatenData();

		EatenData(const float weightValue);
	};

	class EatenComponent : public Component
	{
		EatenData m_eatenData;
	public:
		EatenComponent(std::shared_ptr<GameObject>& owner,const EatenData& eatenData);

		EatenData GetEatenData() const;

		void OnUpdate() override {}
	};
}