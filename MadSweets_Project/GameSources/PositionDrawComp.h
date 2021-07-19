/*!
@file PositionDrawComp.h
@brief PositionDrawComp
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

namespace basecross {

	class PositionDrawComp : public Component
	{

	public:

		PositionDrawComp(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnUpdate() override;
	};

}

//endbasecross