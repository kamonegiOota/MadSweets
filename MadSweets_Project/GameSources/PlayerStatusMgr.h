/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "I_Damaged.h"

namespace basecross {

	enum class PlayerStaus {
		Nomal,
		Dest, //死亡状態
		Destroy, //死亡演出が終了して完全に死んだ状態。
	};

	struct PlayerStatusParam {
		float hp = 10.0f;
		PlayerStaus state = PlayerStaus::Nomal;
	};

	/// <summary>
	/// playerのステータスのコンポーネント
	/// </summary>
	class PlayerStatusMgr : public Component , public I_Damaged
	{
		PlayerStatusParam m_param;

	public:
		PlayerStatusMgr(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}
		 
		void OnCreate() override{}
		void OnUpdate() override;

		//インターフェースの実装
		void Damage(const float& damage) override;

		//アクセッサ---------------------------------------------------------
		void ChangeState(const PlayerStaus& state) {
			m_param.state = state;
		}
		PlayerStaus GetState() const {
			return m_param.state;
		}

	};

}

//endbasecross