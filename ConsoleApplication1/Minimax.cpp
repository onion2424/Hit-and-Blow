#include "Minimax.h"
#include "Common.h"

#include <future>
#include <vector>
#include <iostream>
using namespace std;

__m128i* MiniMax::searchField; //�T���p�̃t�B�[���h
__m128i* MiniMax::bitY;
__m128i* MiniMax::notY;
__m128i* MiniMax::bitZ;
__m128i* MiniMax::notZ;



//�R���X�g���N�^�i�g��Ȃ��j
MiniMax::MiniMax()
{

}

void MiniMax::getMaxNum(int a, int b, int c)
{
	__m128i tmp_field[9][10] = {};

	//�c��̌�␔��Ԃ�
	int minArray[9];
	int max = 0;
	int sum = 0;


	//�傫�����ɂ���
	const int S = (a < b) ? (a < c) ? a : c : (b < c) ? b : c;
	const int M = (a < b) ? (b < c) ? b : (a < c) ? c : a : (c < b) ? b : (a < c) ? a : c;
	const int L = (a < b) ? (b < c) ? c : b : (a > c) ? a : c;


	//hit3 blow0
	tmp_field[0][a] = _mm_and_si128(_mm_and_si128(possible[a], bitY[b]), bitZ[c]);
	tmp_field[0][(a + 1) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 2) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 3) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 4) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 5) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 6) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 7) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 8) % 10] = _mm_setzero_si128();
	tmp_field[0][(a + 9) % 10] = _mm_setzero_si128();
	minArray[0] = bitCount(tmp_field[0]);


	//hit0 blow3
	tmp_field[1][b] = _mm_and_si128(_mm_and_si128(possible[b], bitY[c]), bitZ[a]);
	tmp_field[1][c] = _mm_and_si128(_mm_and_si128(possible[c], bitY[a]), bitZ[b]);
	//b��c�̊�
	for (int idx = (b < c ? b : c) + 1; idx < (b < c ? c : b); idx++) {
		tmp_field[1][idx] = _mm_setzero_si128();
	}
	//b��c�̊O
	for (int idx = ((b < c ? c : b) + 1); idx < (b < c ? b : c) + 10; idx++) {
		tmp_field[1][idx % 10] = _mm_setzero_si128();
	}
	minArray[1] = bitCount(tmp_field[1]);



	//hit1 blow2
	tmp_field[2][a] = _mm_and_si128(_mm_and_si128(possible[a], bitY[c]), bitZ[b]);
	tmp_field[2][b] = _mm_and_si128(_mm_and_si128(possible[b], bitY[a]), bitZ[c]);
	tmp_field[2][c] = _mm_and_si128(_mm_and_si128(possible[c], bitY[b]), bitZ[a]);
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[2][idx] = _mm_setzero_si128();
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[2][idx] = _mm_setzero_si128();
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[2][idx % 10] = _mm_setzero_si128();
	}
	minArray[2] = bitCount(tmp_field[2]);



	//hit2 blow0
	//a�̂Ƃ� 
	tmp_field[3][a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(possible[a], bitY[b]), notZ[c]), _mm_and_si128(_mm_and_si128(possible[a], notY[b]), bitZ[c]));
	//���ꂢ����
	tmp_field[3][(a + 1) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 1) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 2) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 2) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 3) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 3) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 4) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 4) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 5) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 5) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 6) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 6) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 7) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 7) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 8) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 8) % 10], bitY[b]), bitZ[c]);
	tmp_field[3][(a + 9) % 10] = _mm_and_si128(_mm_and_si128(possible[(a + 9) % 10], bitY[b]), bitZ[c]);
	minArray[3] = bitCount(tmp_field[3]);


	//hit 1 blow1
	//abc�̎�
	tmp_field[4][a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(possible[a], bitY[c]), notZ[b]), _mm_and_si128(_mm_and_si128(possible[a], notY[c]), bitZ[b]));
	tmp_field[4][b] = _mm_and_si128(_mm_and_si128(possible[b], notY[a]), bitZ[c]);
	tmp_field[4][c] = _mm_and_si128(_mm_and_si128(possible[c], bitY[b]), notZ[a]);
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[4][idx] = _mm_or_si128(_mm_and_si128(possible[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(possible[idx], _mm_and_si128(bitY[b], bitZ[a])));
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[4][idx] = _mm_or_si128(_mm_and_si128(possible[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(possible[idx], _mm_and_si128(bitY[b], bitZ[a])));
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[4][idx % 10] = _mm_or_si128(_mm_and_si128(possible[idx % 10], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(possible[idx % 10], _mm_and_si128(bitY[b], bitZ[a])));
	}
	minArray[4] = bitCount(tmp_field[4]);



	//hit0 blow2
	//abc�̎�
	tmp_field[5][a] = _mm_setzero_si128();
	tmp_field[5][b] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[b], bitY[a]), notZ[c]), _mm_and_si128(_mm_and_si128(possible[b], bitY[c]), notZ[a])), _mm_and_si128(_mm_and_si128(possible[b], notY[c]), bitZ[a]));
	tmp_field[5][c] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[c], bitY[a]), notZ[b]), _mm_and_si128(_mm_and_si128(possible[c], notY[b]), bitZ[a])), _mm_and_si128(_mm_and_si128(possible[c], notY[a]), bitZ[b]));
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[5][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(possible[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), bitZ[a]));
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[5][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(possible[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), bitZ[a]));
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[5][idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[c]), bitZ[a]));
	}
	minArray[5] = bitCount(tmp_field[5]);



	//hit1 blow0
	tmp_field[6][a] = _mm_and_si128(_mm_and_si128(possible[a], _mm_and_si128(notY[b], notY[c])), _mm_and_si128(notZ[b], notZ[c]));
	tmp_field[6][b] = _mm_setzero_si128();
	tmp_field[6][c] = _mm_setzero_si128();
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[6][idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[6][idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[6][idx % 10] = _mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(possible[idx % 10], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
	}
	minArray[6] = bitCount(tmp_field[6]);



	//hit0 blow0
	tmp_field[7][a] = _mm_setzero_si128();
	tmp_field[7][b] = _mm_setzero_si128();
	tmp_field[7][c] = _mm_setzero_si128();
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[7][idx] = _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[7][idx] = _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[7][idx % 10] = _mm_and_si128(_mm_and_si128(possible[idx % 10], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
	}
	minArray[7] = bitCount(tmp_field[7]);



	//hit0 blow1
	tmp_field[8][a] = _mm_setzero_si128();
	tmp_field[8][b] = _mm_and_si128(possible[b], _mm_and_si128(_mm_and_si128(notY[a], notY[c]), _mm_and_si128(notZ[a], notZ[c])));
	tmp_field[8][c] = _mm_and_si128(possible[c], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), _mm_and_si128(notZ[a], notZ[b])));
	//S��M�̊�
	for (int idx = S + 1; idx < M; idx++) {
		tmp_field[8][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
	}
	//M��L�̊�
	for (int idx = M + 1; idx < L; idx++) {
		tmp_field[8][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(possible[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
	}
	//L��S�̊�
	for (int idx = L + 1; idx < S + 10; idx++) {
		tmp_field[8][idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(possible[idx % 10], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(possible[idx % 10], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(possible[idx % 10], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
	}
	minArray[8] = bitCount(tmp_field[8]);

	for (int i = 0; i < 9; i++) {
		if (max < minArray[i]) {
			max = minArray[i];

			//field_cp�ɍő�l�̂Ƃ��̃t�B�[���h����������
			memcpy(possible, tmp_field[i], sizeof(tmp_field[i]));
		}
		sum += minArray[i];
	}
	if (sum > 0 && sum - minArray[0] == 0) { //�ς����� i��ۑ����Ă����� -1�Ȃ�1000 1 �Ȃ�-1�ɂ˂��Ȃ���΂����isum�݂Ȃ��Ƃ����Ȃ��H�j
		maxNum = -1;
	}
	else {
		maxNum = max > 0 ? max : 1000; //0�̂Ƃ���1000�ɂ���
	}
	return;
}

