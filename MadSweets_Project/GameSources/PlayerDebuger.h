#pragma once
#include"CameraComponent.h"
#include"PlayerObject.h"
#include"PlayerRotater.h"
namespace basecross
{
	class PlayerDebuger : public Component
	{
		ex_weak_ptr<CameraComponent> m_defaultCamera;
		ex_weak_ptr<CameraComponent> m_debugCamera;
		ex_weak_ptr<PlayerRotater> m_playerRotater;

		bool m_isCameraDebug = false;

		void CameraDebug();
	public:
		PlayerDebuger(std::shared_ptr<GameObject>& owner,
			const std::shared_ptr<CameraComponent>& defalutCamera,const std::shared_ptr<CameraComponent>& debugCamera,
			const std::shared_ptr<PlayerObject>& player);

		void OnUpdate() override;
	};
}