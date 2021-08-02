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

		virtual std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) = 0;
	};
}