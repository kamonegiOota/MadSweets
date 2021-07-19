/*!
@file MargeTestStage.h
@brief MargeTestStage
’S“–ÒFŠÛR —TŠì
*/

#pragma once

namespace basecross {

	class MargeTestStage : public Stage
	{

		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}

		virtual void CreateMap(const wstring& fileName);

	};

}

//endbasecross