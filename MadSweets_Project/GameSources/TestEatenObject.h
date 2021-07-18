#pragma once

namespace basecross
{
	class TestEatenObject : public GameObject
	{
	public:
		TestEatenObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
	};
}