#pragma once

namespace basecross
{
	class GameItem
	{
		std::wstring m_name;

	public:

		GameItem() : GameItem(L"") {}

		GameItem(const std::wstring& name) :
			m_name(name)
		{

		}

		std::wstring GetName() const { return m_name; }

		bool operator==(const GameItem& gameItem) const
		{
			return m_name == gameItem.GetName();
		}

		bool operator!=(const GameItem& gameItem) const
		{
			return !((*this) == gameItem);
		}
	};
}