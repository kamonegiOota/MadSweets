#include"OptionMainMenuButtonEventer.h"

namespace basecross
{
	OptionMainMenuButtonEventer::OptionMainMenuButtonEventer(std::shared_ptr<GameObject>& owner,
		const std::shared_ptr<GameObject>& subOptionMenu) :
		Component(owner),
		m_subOptionMenu(subOptionMenu)
	{

	}

	void OptionMainMenuButtonEventer::OnSelect()
	{
		if (m_subOptionMenu)
		{
			m_isGoSubMenu = false;
			m_subOptionMenu->SetActive(true);
		}
	}

	void OptionMainMenuButtonEventer::OnPush()
	{
		std::shared_ptr<I_Selectable> selectable = nullptr;

		if (m_subOptionMenu)
		{
			for (auto& child : m_subOptionMenu->GetChildren())
			{
				if (!child->GetUpdateActive())
				{
					continue;
				}

				selectable = child->GetComponent<I_Selectable>(false);

				if (selectable)
				{
					break;
				}

			}
		}

		EventSystem::GetInstance(GetStage())->PushSelectable(selectable);
	}

	void OptionMainMenuButtonEventer::OnoutSelect()
	{
		if (m_subOptionMenu && !m_isGoSubMenu)
		{
			m_subOptionMenu->SetActive(false);
		}
	}

	void OptionMainMenuButtonEventer::OnStart()
	{
		if (m_subOptionMenu)
		{
			m_subOptionMenu->SetActive(false);
		}
	}
}