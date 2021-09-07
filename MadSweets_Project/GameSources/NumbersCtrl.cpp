
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "NumbersCtrl.h"
#include "Number.h"
#include "NumberObject.h"

#include "Mathf.h"

#include "DebugObject.h"

namespace basecross {

	void NumbersCtrl::CreateNumberObjs() {
		for (int i = 0; i < m_maxDigit; i++) {
			ex_weak_ptr<NumberObject> numberObj = GetStage()->Instantiate<NumberObject>(Vec3(0.0f), Quat::Identity(), GetGameObject());
			m_numberObjs.push_back(numberObj);
		}
	}

	void NumbersCtrl::ChangeDrawNumbers() {
		int index = 0;
		bool isReview = true;  //�R�����邩�ǂ���
		for (auto& numberObj : m_numberObjs) {
			if (index == m_numberObjs.size() - 1) { //��ԉ��̌��������珈�������Ȃ�
				break;
			}

			auto numberComp = numberObj->GetComponent<Number>();
			auto num = numberComp->GetNumber();

			//��x0�ȊO���ł��炻��ȍ~�͕\������B
			if (num == 0 && isReview) {
				numberObj->SetDrawActive(false);
			}
			else {
				numberObj->SetDrawActive(true);
				isReview = false;
			}

			index++;
		}
	}

	void NumbersCtrl::SetNumbersPosition() {
		Vec3 scale = transform->GetScale() / static_cast<float>(m_maxDigit);
		Vec3 basePosition(0.0f);
		Vec3 offset(scale.x, 0.0f, 0.0f);

		int index = 0;
		for (auto& numberObj : m_numberObjs) {
			if (!numberObj->GetDrawActive()) {  //�\������Ă��Ȃ�������
				continue;
			}

			auto createPosition = basePosition + (offset * (float)index++);
			auto numberTrans = numberObj->GetComponent<Transform>();
			numberTrans->SetPosition(createPosition);
			numberTrans->SetScale(scale);
		}
	}

	void NumbersCtrl::OnCreate() {
		CreateNumberObjs();

		SetValue(m_value);
	}

	void NumbersCtrl::SetValue(const int& value) {
		//�����̃Z�b�g
		int place = static_cast<int>(pow(10, m_numberObjs.size() - 1));
		int maxValue = (place * 10) - 1;

		auto m_value = maru::Mathf::Clamp(value, 0, maxValue); //�ő吔�`�F�b�N

		for (auto& numberObj : m_numberObjs) {
			if (!numberObj) {  //null�������珈�����΂��B
				continue;
			}

			int num = m_value / place % 10;  //���o�����������擾
			place /= 10;

			auto numberComp = numberObj->GetComponent<Number>();
			numberComp->SetNumber(num);
		}

		ChangeDrawNumbers();
		SetNumbersPosition();
	}
}

//endbasecross