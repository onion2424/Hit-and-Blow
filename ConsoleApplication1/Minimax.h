#pragma once
#include <emmintrin.h>
#include <vector>
class MiniMax
{



public:
	//�����̉\��
	__m128i possible[10];

	//�萔
	static __m128i* searchField;
	static __m128i* bitY;
	static __m128i* notY;
	static __m128i* bitZ;
	static __m128i* notZ;

	//���n���ɍi�邽�߂̌��l�ő�
	int maxNum;

	//�R���X�g���N�^
	MiniMax();

	//9�p�^�[���̉�������\���ő�̎��T��(field�ɕύX��������)
	void getMaxNum(int a, int b, int c);

};