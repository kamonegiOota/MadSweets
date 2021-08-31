#pragma once
#include"EventedComponent.h"
#include"PlayerGameItemGetter.h"
#include"MessageWindow.h"
#include"GameMessageWindowObject.h"
#include"PlayerMover.h"
#include"AlphaFadeCtrl.h"

namespace basecross
{
	class PlayerOpenDoorManager : public Component, public I_EventComponent
	{
		ex_weak_ptr<PlayerGameItemGetter> m_gameItemGetter;

		ex_weak_ptr<GameMessageWindowObject> m_messageWindowObject;
		ex_weak_ptr<MessageWindow> m_messageWindow;

		ex_weak_ptr<PlayerMover> m_mover;

		ex_weak_ptr<AlphaFadeCtrl> m_alphaFade;

		GameItem m_findGameItem = GameItem(L"Key");

		void MessageWindowFinish();

		bool m_isOneFlameSkip = false;
	public:
		PlayerOpenDoorManager(std::shared_ptr<GameObject>& owner);

		void OnStart() override;

		void OnEvent() override;
	};
}