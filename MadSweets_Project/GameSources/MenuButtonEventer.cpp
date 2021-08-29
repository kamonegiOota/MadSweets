#include"MenuButtonEventer.h"

namespace basecross
{
	MenuButtonEventer::MenuButtonEventer(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void MenuButtonEventer::OnSelectSetDiffuse()
	{
		m_image->SetDiffuse(Col4(1, 1, 1, 1));
	}

	void MenuButtonEventer::OnOutSelectSetDiffuse()
	{
		m_image->SetDiffuse(Col4(0.75f,0.75f,0.75f,1.0f));
	}

	void MenuButtonEventer::OnStart()
	{
		m_image = GetGameObject()->GetComponent<Image>();
		m_image->SetDiffuse(Col4(0.75f, 0.75f, 0.75f, 1.0f));
	}
}