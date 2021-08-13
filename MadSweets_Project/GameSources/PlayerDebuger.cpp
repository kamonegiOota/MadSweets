#include"PlayerDebuger.h"
#include"PlayerInputer.h"

namespace basecross
{
	PlayerDebuger::PlayerDebuger(std::shared_ptr<GameObject>& owner,
		const std::shared_ptr<CameraComponent>& defaultCamera, const std::shared_ptr<CameraComponent>& debugCamera,
		const std::shared_ptr<PlayerObject>& player) :
		Component(owner),
		m_defaultCamera(defaultCamera),
		m_debugCamera(debugCamera),
		m_playerRotater(player->GetComponent<PlayerRotater>())
	{

	}

	void PlayerDebuger::CameraDebug()
	{
		if (!m_defaultCamera || !m_debugCamera)
		{
			return;
		}

		if (!App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::LeftThumb))
		{
			return;
		}

		if (m_isCameraDebug)
		{
			m_debugCamera->GetGameObject()->SetActive(false);
			m_defaultCamera->GetGameObject()->SetActive(true);
		}
		else
		{
			m_defaultCamera->GetGameObject()->SetActive(false);
			m_debugCamera->GetGameObject()->SetActive(true);
		}

		if (m_playerRotater)
		{
			m_playerRotater->SetUpdateActive(m_isCameraDebug);
		}

		m_isCameraDebug = !m_isCameraDebug;
	}

	void PlayerDebuger::OnUpdate()
	{
		CameraDebug();
	}
}