#pragma once

namespace basecross
{
	class MenuButtonEventer : public Component
	{
		ex_weak_ptr<Image> m_image;
	public:
		MenuButtonEventer(std::shared_ptr<GameObject>& owner);

		void OnSelectSetDiffuse();

		void OnOutSelectSetDiffuse();

		void OnStart();
	};
}