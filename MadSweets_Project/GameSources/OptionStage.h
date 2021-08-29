#pragma once

namespace basecross
{
	class OptionStage : public Stage
	{
		std::shared_ptr<UIObject> CreateSoundManageMenuObject(const Vec2& position);

		void OptionSaveLoad();
	public:
		OptionStage();

		void OnCreate() override;
	};
}