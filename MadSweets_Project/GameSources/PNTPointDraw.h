/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class PNTPointDraw :public BcBaseDraw
	{
		struct Impl;
		unique_ptr<Impl> m_pImpl;

		void DrawStatic2(const MeshPrimData& data);
		void SetConstants2(BasicConstants& BcCb, const MeshPrimData& data);

	public :
		PNTPointDraw(const std::shared_ptr<GameObject>& objPtr);

		void OnCreate() override;
		void OnUpdate() override{}

		void OnDraw() override;

	};

}

//endbasecross