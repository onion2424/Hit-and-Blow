#pragma once
#include <emmintrin.h>

class GameInfo
{

	//�I��������
	int target[3];
	//hitBlow�i�[�p
	int hb[2]; //2bit 2bit��4bit�ŕ\�����
	//����ڂ�
	int turn;

	//bit�v�Z�p
	__m128i bitY[10];
	__m128i notY[10];
	__m128i bitZ[10];
	__m128i notZ[10];


public:
	//128bit�̔z��
	__m128i field[10];

	//�e�X�g�p����
	int first[3];

	//����
	int ans[3];

	//�萔�錾
	const int RANGE = 720;
	const int LOOP = 10; //n��s��

	//�R���X�g���N�^
	GameInfo();

	//***************�����ݒ�******************
	//������
	void init();

	//�t�B�[���h���Z�b�g
	void setField();
	//�t�B�[���h���Q�b�g
	__m128i* getField();
	__m128i* getBitY();
	__m128i* getNotY();
	__m128i* getBitZ();
	__m128i* getNotZ();

	//�����������_���ɑI��
	void setAnswer();

	//����������_���ɑI��
	void setFirstTarget();


	//**************************************************


	//�w�肳�ꂽ��ɃZ�b�g����
	void setTarget(int arr[]);

	//�w�肳�ꂽHB�ɃZ�b�g����
	void setHitBlow(int arr[]);

	//�����_����3�����쐬
	void makeRandom(int arr[]);
	



	//*********:�Q�[���I�����f*************:

	bool isEnd();

	//�t�B�[���h���X�V����
	int updateField();

	//hit blow ���m�F����
	void hitBlow();

	//**************************************





	//**************�\���n***
	
	//�I���������\��
	void showTarget();
	//������\��
	void showAnswer();
	//hitblow��\��
	void showHitBlow();



	//**************���v�p***********

	//�z��
	int turnArray[10] = {}; //0�ŏ������\��?
	int optionArray[10] = {};

	//�I���㏈��
	void gameEnd();
};