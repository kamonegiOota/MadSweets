/*!
@file GraphEdge.h
@brief GraphEdge
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class GraphEdge
	{
	protected:
		//�G�b�W�͓�̃m�[�h��A������B
		//�L���m�[�h�͏�ɐ�
		int m_from;
		int m_to;

		float m_cost;  //�ړ��̃R�X�g

	public:

		GraphEdge();
		GraphEdge(const int& from, const int& to);
		GraphEdge(const int& from, const int& to, const float& cost);
		virtual ~GraphEdge() {}

		//�A�N�Z�b�T-------------------------------------------------------
		
		//�t�����g
		int GetFrom() const {
			return m_from;
		}
		void SetFrom(const int& from) {
			m_from = from;
		}

		//�o�b�N
		int GetTo() const {   
			return m_to;
		}
		void SetTo(const int& to) {
			m_to = to;
		}

		//�R�X�g
		float GetCost() const { 
			return m_cost;
		}
		void SetCost(const float& cost) {
			m_cost = cost;
		}
	};

}
//end basecross