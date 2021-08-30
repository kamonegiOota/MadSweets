#pragma once

namespace basecross
{
	class DoorObject : public GameObject
	{
	public:
		DoorObject(std::shared_ptr<Stage>& stage);

		void OnCreate() override;
	};
}