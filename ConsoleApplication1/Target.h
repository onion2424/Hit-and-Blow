//#pragma once
//#include <emmintrin.h>
//class Target
//{
//
//	//�t�B�[���h�R�s�[
//	__m128i field_cp[9][10];
//
//
//public:
//	//�t�B�[���h
//	static __m128i *field;
//	static __m128i *bitY;
//	static __m128i *notY;
//	static __m128i *bitZ;
//	static __m128i *notZ;
//
//	//���n���ɍi�邽�߂̌��l�ő�
//	int maxNum;
//	//3���̓����鐔��
//	int target[3];
//
//	//// ���̎�
//	//int nextTarget[3];
//
//	//�R���X�g���N�^
//	Target();
//	Target(int first, int second, int third);
//	
//	//9�p�^�[���̉�������\���ő�̎��T��(field_cp�ɕύX��������)
//	void getMaxNum();
//	
//	//1��悩��ő���I��
//	void nextTarget(); //����ł����Ȃ�
//	int fullSearch(int pat);
//
//	
//};