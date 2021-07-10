/*!
@file GraphEdge.cpp
@brief GraphEdge����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class GraphEdge
	{
	protected:
		//�G�b�W�͓�̃m�[�h��A������B
		//�L���m�[�h�͏�ɐ�
		int m_front;
		int m_back;

		float m_cost;  //�ړ��̃R�X�g

	public:

		GraphEdge();
		GraphEdge(const int& front, const int& back);
		GraphEdge(const int& front, const int& back, const int& cost);
		virtual ~GraphEdge() {}

		//�A�N�Z�b�T-------------------------------------------------------
		
		//�t�����g
		int GetFront() const {  
			return m_front;
		}
		void SetFront(const int& front) {
			m_front = front;
		}

		//�o�b�N
		int GetBack() const {   
			return m_back;
		}
		void SetBack(const int& back) {
			m_back = back;
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