#pragma once

namespace basecross
{

	class ChoicesComponentBase : public Component
	{
	public:
		ChoicesComponentBase(std::shared_ptr<GameObject>& owner) :
			Component(owner)
		{

		}

		virtual ChoicesObjectAndEvent GetChoicesObjectAndEvent(std::shared_ptr<GameObject>& selectorObject) const = 0;
	};
}