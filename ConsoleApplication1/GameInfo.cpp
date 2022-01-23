#include "GameInfo.h"
#include "Common.h"

#include <iostream>
#include <vector>
#include <random>



GameInfo::GameInfo()
{
	init();
}

//�����ݒ�
void GameInfo::init()
{
	//bitY���Z�b�g
	bitY[0] = _mm_set_epi64x(0b0000000000000000000000000000000000000000000000000000000000000000, 0b011111111100000000000000000000000000);
	bitY[1] = _mm_set_epi64x(0b0000000000000000000000000000000000000000000000000000000000000000, 0b000000000010111111110000000000000000);
	bitY[2] = _mm_set_epi64x(0b0000000000000000000000000000000000000000000000000000000000000000, 0b000000000000000000001101111111000000);
	bitY[3] = _mm_set_epi64x(0b1111000000000000000000000000000000000000000000000000000000000000, 0b000000000000000000000000000000111011);
	bitY[4] = _mm_set_epi64x(0b0000111101111100000000000000000000000000000000000000000000000000, 0b000000000000000000000000000000000000);
	bitY[5] = _mm_set_epi64x(0b0000000000000011111011110000000000000000000000000000000000000000, 0b000000000000000000000000000000000000);
	bitY[6] = _mm_set_epi64x(0b0000000000000000000000001111110111000000000000000000000000000000, 0b000000000000000000000000000000000000);
	bitY[7] = _mm_set_epi64x(0b0000000000000000000000000000000000111111101100000000000000000000, 0b000000000000000000000000000000000000);
	bitY[8] = _mm_set_epi64x(0b0000000000000000000000000000000000000000000011111111010000000000, 0b000000000000000000000000000000000000);
	bitY[9] = _mm_set_epi64x(0b0000000000000000000000000000000000000000000000000000001111111110, 0b000000000000000000000000000000000000);

	//notZ���Z�b�g
	notY[0] = _mm_set_epi64x(0b1111111111111111111111111111111111111111111111111111111111111111, 0b000000000011111111111111111111111111);
	notY[1] = _mm_set_epi64x(0b1111111111111111111111111111111111111111111111111111111111111111, 0b111111111100000000001111111111111111);
	notY[2] = _mm_set_epi64x(0b1111111111111111111111111111111111111111111111111111111111111111, 0b111111111111111111110000000000111111);
	notY[3] = _mm_set_epi64x(0b0000111111111111111111111111111111111111111111111111111111111111, 0b111111111111111111111111111111000000);
	notY[4] = _mm_set_epi64x(0b1111000000000011111111111111111111111111111111111111111111111111, 0b111111111111111111111111111111111111);
	notY[5] = _mm_set_epi64x(0b1111111111111100000000001111111111111111111111111111111111111111, 0b111111111111111111111111111111111111);
	notY[6] = _mm_set_epi64x(0b1111111111111111111111110000000000111111111111111111111111111111, 0b111111111111111111111111111111111111);
	notY[7] = _mm_set_epi64x(0b1111111111111111111111111111111111000000000011111111111111111111, 0b111111111111111111111111111111111111);
	notY[8] = _mm_set_epi64x(0b1111111111111111111111111111111111111111111100000000001111111111, 0b111111111111111111111111111111111111);
	notY[9] = _mm_set_epi64x(0b1111111111111111111111111111111111111111111111111111110000000000, 0b111111111111111111111111111111111111);

	//bitZ���Z�b�g
	bitZ[0] = _mm_set_epi64x(0b0000100000000010000000001000000000100000000010000000001000000000, 0b000000000010000000001000000000100000);
	bitZ[1] = _mm_set_epi64x(0b0000010000000001000000000100000000010000000001000000000100000000, 0b010000000000000000000100000000010000);
	bitZ[2] = _mm_set_epi64x(0b0000001000000000100000000010000000001000000000100000000010000000, 0b001000000000100000000000000000001000);
	bitZ[3] = _mm_set_epi64x(0b0000000100000000010000000001000000000100000000010000000001000000, 0b000100000000010000000001000000000000);
	bitZ[4] = _mm_set_epi64x(0b0000000000000000001000000000100000000010000000001000000000100000, 0b000010000000001000000000100000000010);
	bitZ[5] = _mm_set_epi64x(0b0000000001000000000000000000010000000001000000000100000000010000, 0b000001000000000100000000010000000001);
	bitZ[6] = _mm_set_epi64x(0b1000000000100000000010000000000000000000100000000010000000001000, 0b000000100000000010000000001000000000);
	bitZ[7] = _mm_set_epi64x(0b0100000000010000000001000000000100000000000000000001000000000100, 0b000000010000000001000000000100000000);
	bitZ[8] = _mm_set_epi64x(0b0010000000001000000000100000000010000000001000000000000000000010, 0b000000001000000000100000000010000000);
	bitZ[9] = _mm_set_epi64x(0b0001000000000100000000010000000001000000000100000000010000000000, 0b000000000100000000010000000001000000);

	//notZ���Z�b�g
	notZ[0] = _mm_set_epi64x(0b1111011111111101111111110111111111011111111101111111110111111111, 0b011111111101111111110111111111011111);
	notZ[1] = _mm_set_epi64x(0b1111101111111110111111111011111111101111111110111111111011111111, 0b101111111110111111111011111111101111);
	notZ[2] = _mm_set_epi64x(0b1111110111111111011111111101111111110111111111011111111101111111, 0b110111111111011111111101111111110111);
	notZ[3] = _mm_set_epi64x(0b1111111011111111101111111110111111111011111111101111111110111111, 0b111011111111101111111110111111111011);
	notZ[4] = _mm_set_epi64x(0b1111111101111111110111111111011111111101111111110111111111011111, 0b111101111111110111111111011111111101);
	notZ[5] = _mm_set_epi64x(0b1111111110111111111011111111101111111110111111111011111111101111, 0b111110111111111011111111101111111110);
	notZ[6] = _mm_set_epi64x(0b0111111111011111111101111111110111111111011111111101111111110111, 0b111111011111111101111111110111111111);
	notZ[7] = _mm_set_epi64x(0b1011111111101111111110111111111011111111101111111110111111111011, 0b111111101111111110111111111011111111);
	notZ[8] = _mm_set_epi64x(0b1101111111110111111111011111111101111111110111111111011111111101, 0b111111110111111111011111111101111111);
	notZ[9] = _mm_set_epi64x(0b1110111111111011111111101111111110111111111011111111101111111110, 0b111111111011111111101111111110111111);
	return;
}

//�t�B�[���h��������ԂɃZ�b�g
void GameInfo::setField()
{
	//�ݒ肷�邽�߂�64bit�����l��2��
	field[0] = _mm_set_epi64x(0b1111011101111101111011110111110111011111101101111111010111111110, 0b000000000000111111110101111111011011);
	field[1] = _mm_set_epi64x(0b1111101101111110111011111011110111101111101110111111011011111110, 0b001111111100000000001001111111101011);
	field[2] = _mm_set_epi64x(0b1111110101111111011011111101110111110111101111011111011101111110, 0b010111111110011111110000000000110011);
	field[3] = _mm_set_epi64x(0b0000111001111111101011111110110111111011101111101111011110111110, 0b011011111110101111111100111111000000);
	field[4] = _mm_set_epi64x(0b1111000000000011110011111111010111111101101111110111011111011110, 0b011101111110110111111101011111111001);
	field[5] = _mm_set_epi64x(0b1111111100111100000000001111100111111110101111111011011111101110, 0b011110111110111011111101101111111010);
	field[6] = _mm_set_epi64x(0b0111111101011111111001110000000000111111001111111101011111110110, 0b011111011110111101111101110111111011);
	field[7] = _mm_set_epi64x(0b1011111101101111111010111111110011000000000011111110011111111010, 0b011111101110111110111101111011111011);
	field[8] = _mm_set_epi64x(0b1101111101110111111011011111110101111111100100000000001111111100, 0b011111110110111111011101111101111011);
	field[9] = _mm_set_epi64x(0b1110111101111011111011101111110110111111101011111111000000000000, 0b011111111010111111101101111110111011);
	return;
}

__m128i *GameInfo::getField()
{
	return field;
}
__m128i *GameInfo::getBitY()
{
	return bitY;
}
__m128i *GameInfo::getNotY()
{
	return notY;
}
__m128i *GameInfo::getBitZ()
{
	return bitZ;
}
__m128i *GameInfo::getNotZ()
{
	return notZ;
}

//�����������_���ɑI��
void GameInfo::setAnswer()
{
	//ans[0] = 0;
	//ans[1] = 3;
    //ans[2] = 7;
	makeRandom(ans);
}

//����������_���ɑI��
void GameInfo::setFirstTarget()
{
	//target[0] = 6;
	//target[1] = 4;
	//target[2] = 5;
	makeRandom(target);
	first[0] = target[0], first[1] = target[1], first[2] = target[2];
	return;
}

//�^�[�Q�b�g��ݒ肷��
void GameInfo::setTarget(int arr[])
{
	target[0] = arr[0];
	target[1] = arr[1];
	target[2] = arr[2];
	return;
}

//�q�b�g�u���[��ݒ肷��
void GameInfo::setHitBlow(int arr[]) {
	hb[0] = arr[0];
	hb[1] = arr[1];
}

//************************�I�����f�n********************************

//3-0�Ȃ�false���ꂢ�����Ȃ�true
bool GameInfo::isEnd()
{
	hitBlow();
	if (hb[0] == 3) return true;
	else return false;
}


//���i�߂�
int GameInfo::updateField()
{
	//Pattern pat;
	int hitblow = (hb[0] << 2) | hb[1];

	//abc�ɕ�������
	const int a = target[0];
	const int b = target[1];
	const int c = target[2];

	//�傫�����ɂ���
	const int S = (a < b) ? (a < c) ? a : c : (b < c) ? b : c;
	const int M = (a < b) ? (b < c) ? b : (a < c) ? c : a : (c < b) ? b : (a < c) ? a : c;
	const int L = (a < b) ? (b < c) ? c : b : (a > c) ? a : c;

	switch (hitblow)
	{
	case pat3_0: { //for�͎g��Ȃ��ق�������
		field[a] = _mm_and_si128(_mm_and_si128(field[a], bitY[b]), bitZ[c]);
		field[(a + 1) % 10] = _mm_setzero_si128();
		field[(a + 2) % 10] = _mm_setzero_si128();
		field[(a + 3) % 10] = _mm_setzero_si128();
		field[(a + 4) % 10] = _mm_setzero_si128();
		field[(a + 5) % 10] = _mm_setzero_si128();
		field[(a + 6) % 10] = _mm_setzero_si128();
		field[(a + 7) % 10] = _mm_setzero_si128();
		field[(a + 8) % 10] = _mm_setzero_si128();
		field[(a + 9) % 10] = _mm_setzero_si128();
		break;
	}
	case pat0_3: {
		field[b] = _mm_and_si128(_mm_and_si128(field[b], bitY[c]), bitZ[a]);
		field[c] = _mm_and_si128(_mm_and_si128(field[c], bitY[a]), bitZ[b]);
		//a��b�̊�
		for (int idx = (b < c ? b : c) + 1; idx < (b < c ? c : b); idx++) {
			field[idx] = _mm_setzero_si128();
		}
		//a��b�̊O
		for (int idx = ((b < c ? c : b) + 1); idx < (b < c ? b : c) + 10; idx++) {
			field[idx % 10] = _mm_setzero_si128();
		}

		break;
	}
	case pat1_2: {
		__m128i test1 = _mm_and_si128(field[b], bitY[a]);
		field[a] = _mm_and_si128(_mm_and_si128(field[a], bitY[c]), bitZ[b]);
		field[b] = _mm_and_si128(_mm_and_si128(field[b], bitY[a]), bitZ[c]);
		field[c] = _mm_and_si128(_mm_and_si128(field[c], bitY[b]), bitZ[a]);
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_setzero_si128();
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_setzero_si128();
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_setzero_si128();
		}
		break;
	}
	case pat2_0: {
		//a�̂Ƃ� 
		field[a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[a], bitY[b]), notZ[c]), _mm_and_si128(_mm_and_si128(field[a], notY[b]), bitZ[c]));
		//���ꂢ����
		field[(a + 1) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 1) % 10], bitY[b]), bitZ[c]);
		field[(a + 2) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 2) % 10], bitY[b]), bitZ[c]);
		field[(a + 3) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 3) % 10], bitY[b]), bitZ[c]);
		field[(a + 4) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 4) % 10], bitY[b]), bitZ[c]);
		field[(a + 5) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 5) % 10], bitY[b]), bitZ[c]);
		field[(a + 6) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 6) % 10], bitY[b]), bitZ[c]);
		field[(a + 7) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 7) % 10], bitY[b]), bitZ[c]);
		field[(a + 8) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 8) % 10], bitY[b]), bitZ[c]);
		field[(a + 9) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 9) % 10], bitY[b]), bitZ[c]);
		break;
	}
	case pat1_1: {
		//abc�̎�
		field[a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[a], bitY[c]), notZ[b]), _mm_and_si128(_mm_and_si128(field[a], notY[c]), bitZ[b]));
		field[b] = _mm_and_si128(_mm_and_si128(field[b], notY[a]), bitZ[c]);
		field[c] = _mm_and_si128(_mm_and_si128(field[c], bitY[b]), notZ[a]);
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_or_si128(_mm_and_si128(field[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx], _mm_and_si128(bitY[b], bitZ[a])));
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_or_si128(_mm_and_si128(field[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx], _mm_and_si128(bitY[b], bitZ[a])));
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_or_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx % 10], _mm_and_si128(bitY[b], bitZ[a])));
		}
		break;
	}
	case pat0_2: {
		//abc�̎�
		field[a] = _mm_setzero_si128();
		field[b] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[b], bitY[a]), notZ[c]), _mm_and_si128(_mm_and_si128(field[b], bitY[c]), notZ[a])), _mm_and_si128(_mm_and_si128(field[b], notY[c]), bitZ[a]));
		field[c] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[c], bitY[a]), notZ[b]), _mm_and_si128(_mm_and_si128(field[c], notY[b]), bitZ[a])), _mm_and_si128(_mm_and_si128(field[c], notY[a]), bitZ[b]));
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[a]));
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[a]));
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx % 10], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), bitZ[a]));
		}
		break;
	}
	case pat1_0: {
		field[a] = _mm_and_si128(_mm_and_si128(field[a], _mm_and_si128(notY[b], notY[c])), _mm_and_si128(notZ[b], notZ[c]));
		field[b] = _mm_setzero_si128();
		field[c] = _mm_setzero_si128();
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
		}
		break;
	}
	case pat0_0: {
		field[a] = _mm_setzero_si128();
		field[b] = _mm_setzero_si128();
		field[c] = _mm_setzero_si128();
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
		}
		break;
	}
	case pat0_1: {
		field[a] = _mm_setzero_si128();
		field[b] = _mm_and_si128(field[b], _mm_and_si128(_mm_and_si128(notY[a], notY[c]), _mm_and_si128(notZ[a], notZ[c])));
		field[c] = _mm_and_si128(field[c], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), _mm_and_si128(notZ[a], notZ[b])));
		//S��M�̊�
		for (int idx = S + 1; idx < M; idx++) {
			field[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
				, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
		}
		//M��L�̊�
		for (int idx = M + 1; idx < L; idx++) {
			field[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
				, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
		}
		//L��S�̊�
		for (int idx = L + 1; idx < S + 10; idx++) {
			field[idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
				, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
		}
		break;
	}
	default: {
		//�G���[���b�Z�[�W
		std::cout << "Erro : hit" << hb[0] << " " << "blow" << hb[1] << std::endl;
		break;
	}

	}
	return bitCount(field);
}

//hitblow���m�F����
void GameInfo::hitBlow()
{
	//����m�F (�d���Ȃ��O��) �Ă��Ƃ�������
	hb[0] = 0;
	hb[1] = 0;
	if (target[0] == ans[0]) hb[0]++;
	if (target[1] == ans[1])  hb[0]++;
	if (target[2] == ans[2])  hb[0]++;
	if ((target[0] == ans[1]) || (target[0] == ans[2])) hb[1]++;
	if ((target[1] == ans[0]) || (target[1] == ans[2])) hb[1]++;
	if ((target[2] == ans[1]) || (target[2] == ans[0])) hb[1]++;
	return;
}

//�����_����3�̐�����Ԃ�
void GameInfo::makeRandom(int array[])
{
	//�����_���Ȑ��������p
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, 9);

	//3�̐������i�[����
	std::vector<int> r;
	int num;

	while (r.size() < 3) {
		num = dist(mt);
		for (auto& elm : r) {
			if (elm == num) goto SKIP; //���d���[�v�����邽�߂�goto���͋������H
		}
		r.push_back(num);
	SKIP:
		continue;
	}
	//�Ō�Ɉ����Ŏ󂯎�����z��ɑ������
	array[0] = r[0];
	array[1] = r[1];
	array[2] = r[2];
}

//***********�\���n**************
void GameInfo::showAnswer()
{
	std::cout << "���� : " << ans[0] << ans[1] << ans[2] << std::endl;
	return;
}

void GameInfo::showTarget()
{
	std::cout << "�I���� : " << target[0] << target[1] << target[2] << std::endl;
	return;
}

void GameInfo::showHitBlow() {
	std::cout << "Hit : " << hb[0] << " Blow : " << hb[1] << std::endl;
	return;
}

void GameInfo::gameEnd()
{
	double divisor = LOOP;
	for (int i = 0; i < 10; i++) {
		divisor -= turnArray[i];
		std::cout << i + 1 << "��� : " << turnArray[i] << "��  �c��̌�␔ : " << optionArray[i] / (divisor == 0 ? 1 : divisor) << std::endl;
		
	}

	return; //�܂��Ȃ��ł���
}