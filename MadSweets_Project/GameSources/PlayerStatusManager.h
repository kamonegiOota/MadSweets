/*!
@file PlayerStatusManager.h
@brief PlayerStatusManagerクラス
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
		float maxHp = hp;
		PlayerStaus state = PlayerStaus::Nomal;
	};

	/// <summary>
	/// playerのステータスのコンポーネント
	/// </summary>
	class PlayerStatusManager : public Component , public I_Damaged
	{
		PlayerStatusParam m_param;

		void CreateHitEffect();  //ヒットエフェクトの生成

		void ChangeGameOverStage();
		void DestProcess();

	public:
		PlayerStatusManager(const std::shared_ptr<GameObject>& objPtr)
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

		void SetHP(const float& value) {
			m_param.hp = value;
		}

		void AddHP(const float& value) {
			m_param.hp += value;
		}

		float GetHP() const {
			return m_param.hp;
		}

		float GetMaxHp() const {
			return m_param.maxHp;
		}
		
		/// <summary>
		/// HPの割合を計算して返す
		/// </summary>
		/// <returns>HPの割合</returns>
		float CalucHPRatio() const{
			return m_param.hp / m_param.maxHp;
		}

	};

}

//endbasecross