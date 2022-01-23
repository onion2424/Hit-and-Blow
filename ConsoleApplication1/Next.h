#pragma once
#include "Minimax.h"
#include <vector>
#include <emmintrin.h>

class Next :
	public MiniMax
{
public:
	//���݂̃t�B�[���h��ێ�
	static __m128i* field;
	//�R���X�g���N�^
	Next(int first, int second, int third);
	Next();

	//���̎��ۑ�
	int target[3];

	//�����Ă��邩�ǂ���
	bool isArrive = true;

	//	���̎�̍ő����i�[
	std::vector<MiniMax> mins;


	//�I�[�o�[���C�h
	void getMaxNum();

	
	//	���̎��T��
	void setNext();
	void setNext_step();
};

