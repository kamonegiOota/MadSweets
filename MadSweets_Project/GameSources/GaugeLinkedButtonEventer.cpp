#include"GaugeLinkedButtonEventer.h"

namespace basecross
{
	GaugeLinkedButtonEventer::GaugeLinkedButtonEventer(std::shared_ptr<GameObject>& owner,
		const std::shared_ptr<GaugeManager>& gaugeManager,
		const std::shared_ptr<OptionGaugeOperator>& optionGaugeOperator) :
		Component(owner),
		m_gaugeManager(gaugeManager),
		m_optionGaugeOperator(optionGaugeOperator)
	{

	}

	void GaugeLinkedButtonEventer::OnCreate()
	{
		m_button = GetGameObject()->GetComponent<Button>();
	}

	void GaugeLinkedButtonEventer::OnPush()
	{
		m_isSelectedLock = !m_isSelectedLock;

		m_button->SetIsSelectedLock(m_isSelectedLock);

		m_optionGaugeOperator->SetUpdateActive(m_isSelectedLock);

		auto& diffuse = m_isSelectedLock ? m_activeDiffuse : m_notActiveDiffuse;

		m_gaugeManager->SetDiffuse(diffuse);
	}
}