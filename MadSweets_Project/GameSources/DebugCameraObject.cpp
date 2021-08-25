#include"DebugCameraObject.h"
#include"InputHelper.h"

namespace basecross
{
	DebugCameraObject::DebugCameraObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void DebugCameraObject::OnCreate()
	{
		m_virtualCamera = AddComponent<VirtualCamera>(INT_MAX);
		m_virtualCamera->SetUpdateActive(false);
	}

	void DebugCameraObject::OnUpdate()
	{
		GameObject::OnUpdate();

		if (App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(itbs::Input::XInputCode::LeftThumb))
		{
			m_virtualCamera->SetUpdateActive(!m_virtualCamera->GetUpdateActive());
		}
	}
}