//#include "Target.h"
//#include "Common.h"
//
//#include <future>
//#include <vector>
//#include <iostream>
//using namespace std;
//
//__m128i *Target::field;
//__m128i *Target::bitY;
//__m128i *Target::notY;
//__m128i *Target::bitZ;
//__m128i *Target::notZ;
//
//
//
////�R���X�g���N�^�i�g��Ȃ��j
//Target::Target()
//{
//
//}
//
////�S�p�^�[���쐬���邽�߂̃R���X�g���N�^
//Target::Target(int first, int second, int third)
//{
//	target[0] = first;
//	target[1] = second;
//	target[2] = third;
//	return;
//}
//
////��莟����������
//void Target::nextTarget()
//{
//	int min = 0;
//	int temp = 0;
//	vector<future<int>> threads;
//	//create threads
//	for (int i = 0; i < 9; ++i)
//		//threads.push_back(async(fullSearch, i));
//		threads.push_back(async(launch::async, [i, this]() { return fullSearch(i); }));
//	//wait for them to complete
//	for (auto& th : threads)
//	{
//		temp = th.get();
//		if ((min == 0 || min < temp) && temp > 0) {
//			min = temp;
//		}
//		//min += temp;
//	}
//
//	maxNum = min;
//
//	return;
//}
//
//int Target::fullSearch(int pat) {
//	//�e�X�g�p
//	int target[3];
//
//	//�ϐ���`
//	int ret = 1000; //�߂�l
//	int max = 0;
//
//	__m128i f[10];  //�R�s�[�p
//	__m128i count[10];  //�J�E���g�p
//
//	//�t�B�[���h���R�s�[����(�Ӗ����邩�͕�����񂯂Ǖ�����l�����Ă������)
//	f[0] = field_cp[pat][0];
//	f[1] = field_cp[pat][1];
//	f[2] = field_cp[pat][2];
//	f[3] = field_cp[pat][3];
//	f[4] = field_cp[pat][4];
//	f[5] = field_cp[pat][5];
//	f[6] = field_cp[pat][6];
//	f[7] = field_cp[pat][7];
//	f[8] = field_cp[pat][8];
//	f[9] = field_cp[pat][9];
//
//	//�c��̌�␔��Ԃ�
//	int minArray[9];
//
//	int S, M, L;
//	for (int a = 0; a < 10; a++) {
//		for (int b = 0; b < 10; b++) {
//			if (a == b) continue;
//			for (int c = 0; c < 10; c++) {
//				if (a == c || b == c) continue;
//				//�����ݒ�
//
//				S = (a < b) ? (a < c) ? a : c : (b < c) ? b : c;
//				M = (a < b) ? (b < c) ? b : (a < c) ? c : a : (c < b) ? b : (a < c) ? a : c;
//				L = (a < b) ? (b < c) ? c : b : (a > c) ? a : c;
//
//				//hit3 blow0
//				count[a] = _mm_and_si128(_mm_and_si128(f[a], bitY[b]), bitZ[c]);
//				count[(a + 1) % 10] = _mm_setzero_si128();
//				count[(a + 2) % 10] = _mm_setzero_si128();
//				count[(a + 3) % 10] = _mm_setzero_si128();
//				count[(a + 4) % 10] = _mm_setzero_si128();
//				count[(a + 5) % 10] = _mm_setzero_si128();
//				count[(a + 6) % 10] = _mm_setzero_si128();
//				count[(a + 7) % 10] = _mm_setzero_si128();
//				count[(a + 8) % 10] = _mm_setzero_si128();
//				count[(a + 9) % 10] = _mm_setzero_si128();
//				minArray[0] = bitCount(count);
//
//
//				//hit0 blow3
//				count[b] = _mm_and_si128(_mm_and_si128(f[b], bitY[c]), bitZ[a]);
//				count[c] = _mm_and_si128(_mm_and_si128(f[c], bitY[a]), bitZ[b]);
//				//b��c�̊�
//				for (int idx = (b < c ? b : c) + 1; idx < (b < c ? c : b); idx++) {
//					count[idx] = _mm_setzero_si128();
//				}
//				//b��c�̊O
//				for (int idx = ((b < c ? c : b) + 1); idx < (b < c ? b : c) + 10; idx++) {
//					count[idx % 10] = _mm_setzero_si128();
//				}
//				minArray[1] = bitCount(count);
//
//
//
//				//hit1 blow2
//				count[a] = _mm_and_si128(_mm_and_si128(f[a], bitY[c]), bitZ[b]);
//				count[b] = _mm_and_si128(_mm_and_si128(f[b], bitY[a]), bitZ[c]);
//				count[c] = _mm_and_si128(_mm_and_si128(f[c], bitY[b]), bitZ[a]);
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_setzero_si128();
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_setzero_si128();
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_setzero_si128();
//				}
//				minArray[2] = bitCount(count);
//
//
//
//				//hit2 blow0
//				//a�̂Ƃ� 
//				count[a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(f[a], bitY[b]), notZ[c]), _mm_and_si128(_mm_and_si128(f[a], notY[b]), bitZ[c]));
//				//���ꂢ����
//				count[(a + 1) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 1) % 10], bitY[b]), bitZ[c]);
//				count[(a + 2) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 2) % 10], bitY[b]), bitZ[c]);
//				count[(a + 3) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 3) % 10], bitY[b]), bitZ[c]);
//				count[(a + 4) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 4) % 10], bitY[b]), bitZ[c]);
//				count[(a + 5) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 5) % 10], bitY[b]), bitZ[c]);
//				count[(a + 6) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 6) % 10], bitY[b]), bitZ[c]);
//				count[(a + 7) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 7) % 10], bitY[b]), bitZ[c]);
//				count[(a + 8) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 8) % 10], bitY[b]), bitZ[c]);
//				count[(a + 9) % 10] = _mm_and_si128(_mm_and_si128(f[(a + 9) % 10], bitY[b]), bitZ[c]);
//				minArray[3] = bitCount(count);
//
//
//				//hit 1 blow1
//				//abc�̎�
//				count[a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(f[a], bitY[c]), notZ[b]), _mm_and_si128(_mm_and_si128(f[a], notY[c]), bitZ[b]));
//				count[b] = _mm_and_si128(_mm_and_si128(f[b], notY[a]), bitZ[c]);
//				count[c] = _mm_and_si128(_mm_and_si128(f[c], bitY[b]), notZ[a]);
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_or_si128(_mm_and_si128(f[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(f[idx], _mm_and_si128(bitY[b], bitZ[a])));
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_or_si128(_mm_and_si128(f[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(f[idx], _mm_and_si128(bitY[b], bitZ[a])));
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_or_si128(_mm_and_si128(f[idx % 10], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(f[idx % 10], _mm_and_si128(bitY[b], bitZ[a])));
//				}
//				minArray[4] = bitCount(count);
//
//
//
//				//hit0 blow2
//				//abc�̎�
//				count[a] = _mm_setzero_si128();
//				count[b] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[b], bitY[a]), notZ[c]), _mm_and_si128(_mm_and_si128(f[b], bitY[c]), notZ[a])), _mm_and_si128(_mm_and_si128(f[b], notY[c]), bitZ[a]));
//				count[c] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[c], bitY[a]), notZ[b]), _mm_and_si128(_mm_and_si128(f[c], notY[b]), bitZ[a])), _mm_and_si128(_mm_and_si128(f[c], notY[a]), bitZ[b]));
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(f[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(f[idx], bitY[c]), bitZ[a]));
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(f[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(f[idx], bitY[c]), bitZ[a]));
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx % 10], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(f[idx % 10], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(f[idx % 10], bitY[c]), bitZ[a]));
//				}
//				minArray[5] = bitCount(count);
//
//
//
//				//hit1 blow0
//				count[a] = _mm_and_si128(_mm_and_si128(f[a], _mm_and_si128(notY[b], notY[c])), _mm_and_si128(notZ[b], notZ[c]));
//				count[b] = _mm_setzero_si128();
//				count[c] = _mm_setzero_si128();
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx % 10], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(f[idx % 10], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//				}
//				minArray[6] = bitCount(count);
//
//
//
//				//hit0 blow0
//				count[a] = _mm_setzero_si128();
//				count[b] = _mm_setzero_si128();
//				count[c] = _mm_setzero_si128();
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_and_si128(_mm_and_si128(f[idx % 10], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//				}
//				minArray[7] = bitCount(count);
//
//
//
//				//hit0 blow1
//				count[a] = _mm_setzero_si128();
//				count[b] = _mm_and_si128(f[b], _mm_and_si128(_mm_and_si128(notY[a], notY[c]), _mm_and_si128(notZ[a], notZ[c])));
//				count[c] = _mm_and_si128(f[c], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), _mm_and_si128(notZ[a], notZ[b])));
//				//S��M�̊�
//				for (int idx = S + 1; idx < M; idx++) {
//					count[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//						, (_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//				}
//				//M��L�̊�
//				for (int idx = M + 1; idx < L; idx++) {
//					count[idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//						, (_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(f[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//				}
//				//L��S�̊�
//				for (int idx = L + 1; idx < S + 10; idx++) {
//					count[idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx % 10], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(f[idx % 10], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//						, (_mm_or_si128(_mm_and_si128(_mm_and_si128(f[idx % 10], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(f[idx % 10], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//				}
//				minArray[8] = bitCount(count);
//
//				//array[0]�ɍő�l������
//				for (int i = 1; i < 9; i++) {
//					if (minArray[0] < minArray[i]) minArray[0] = minArray[i];
//				}
//				if (minArray[0] < ret) {
//					ret = minArray[0];
//					//std::cout << pat << " : " << ret << " �� : " << a << b << c << std::endl;
//				}
//			}
//		}
//	}
//
//	
//	return ret ;
//}
////�ő����m�F����
//void Target::getMaxNum()
//{
//	//�c��̌�␔��Ԃ�
//	int minArray[9];
//	int max = 0;
//	int sum = 0;
//
//	//abc�ɕ�������
//	const int a = target[0];
//	const int b = target[1];
//	const int c = target[2];
//
//	//�傫�����ɂ���
//	const int S = (a < b) ? (a < c) ? a : c : (b < c) ? b : c;
//	const int M  = (a < b) ? (b < c) ? b : (a < c) ? c : a : (c < b) ? b : (a < c) ? a : c;
//	const int L = (a < b) ? (b < c) ? c : b : (a > c) ? a : c;
//
//
//	//hit3 blow0
//	field_cp[0][a] = _mm_and_si128(_mm_and_si128(field[a], bitY[b]), bitZ[c]);
//	field_cp[0][(a + 1) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 2) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 3) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 4) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 5) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 6) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 7) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 8) % 10] = _mm_setzero_si128();
//	field_cp[0][(a + 9) % 10] = _mm_setzero_si128();
//	minArray[0] = bitCount(field_cp[0]);
//	
//
//	//hit0 blow3
//	field_cp[1][b] = _mm_and_si128(_mm_and_si128(field[b], bitY[c]), bitZ[a]);
//	field_cp[1][c] = _mm_and_si128(_mm_and_si128(field[c], bitY[a]), bitZ[b]);
//	//b��c�̊�
//	for (int idx = (b < c ? b : c) + 1; idx < (b < c ? c : b); idx++) {
//		field_cp[1][idx] = _mm_setzero_si128();
//	}
//	//b��c�̊O
//	for (int idx = ((b < c ? c : b) + 1); idx < (b < c ? b : c) + 10; idx++) {
//		field_cp[1][idx % 10] = _mm_setzero_si128();
//	}
//	minArray[1] = bitCount(field_cp[1]);
//
//
//
//	//hit1 blow2
//	field_cp[2][a] = _mm_and_si128(_mm_and_si128(field[a], bitY[c]), bitZ[b]);
//	field_cp[2][b] = _mm_and_si128(_mm_and_si128(field[b], bitY[a]), bitZ[c]);
//	field_cp[2][c] = _mm_and_si128(_mm_and_si128(field[c], bitY[b]), bitZ[a]);
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[2][idx] = _mm_setzero_si128();
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[2][idx] = _mm_setzero_si128();
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[2][idx % 10] = _mm_setzero_si128();
//	}
//	minArray[2] = bitCount(field_cp[2]);
//
//
//
//	//hit2 blow0
//	//a�̂Ƃ� 
//	field_cp[3][a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[a], bitY[b]), notZ[c]), _mm_and_si128(_mm_and_si128(field[a], notY[b]), bitZ[c]));
//	//���ꂢ����
//	field_cp[3][(a + 1) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 1) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 2) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 2) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 3) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 3) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 4) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 4) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 5) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 5) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 6) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 6) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 7) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 7) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 8) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 8) % 10], bitY[b]), bitZ[c]);
//	field_cp[3][(a + 9) % 10] = _mm_and_si128(_mm_and_si128(field[(a + 9) % 10], bitY[b]), bitZ[c]);
//	minArray[3] = bitCount(field_cp[3]);
//
//
//	//hit 1 blow1
//	//abc�̎�
//	field_cp[4][a] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[a], bitY[c]), notZ[b]), _mm_and_si128(_mm_and_si128(field[a], notY[c]), bitZ[b]));
//	field_cp[4][b] = _mm_and_si128(_mm_and_si128(field[b], notY[a]), bitZ[c]);
//	field_cp[4][c] = _mm_and_si128(_mm_and_si128(field[c], bitY[b]), notZ[a]);
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[4][idx] = _mm_or_si128(_mm_and_si128(field[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx], _mm_and_si128(bitY[b], bitZ[a])));
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[4][idx] = _mm_or_si128(_mm_and_si128(field[idx], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx], _mm_and_si128(bitY[b], bitZ[a])));
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[4][idx % 10] = _mm_or_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(bitY[a], bitZ[c])), _mm_and_si128(field[idx % 10], _mm_and_si128(bitY[b], bitZ[a])));
//	}
//	minArray[4] = bitCount(field_cp[4]);
//
//
//
//	//hit0 blow2
//	//abc�̎�
//	field_cp[5][a] = _mm_setzero_si128();
//	field_cp[5][b] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[b], bitY[a]), notZ[c]), _mm_and_si128(_mm_and_si128(field[b], bitY[c]), notZ[a])), _mm_and_si128(_mm_and_si128(field[b], notY[c]), bitZ[a]));
//	field_cp[5][c] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[c], bitY[a]), notZ[b]), _mm_and_si128(_mm_and_si128(field[c], notY[b]), bitZ[a])), _mm_and_si128(_mm_and_si128(field[c], notY[a]), bitZ[b]));
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[5][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[a]));
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[5][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx], bitY[c]), bitZ[a]));
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[5][idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), bitZ[b]), _mm_and_si128(_mm_and_si128(field[idx % 10], bitY[a]), bitZ[b])), _mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), bitZ[a]));
//	}
//	minArray[5] = bitCount(field_cp[5]);
//
//
//
//	//hit1 blow0
//	field_cp[6][a] = _mm_and_si128(_mm_and_si128(field[a], _mm_and_si128(notY[b], notY[c])), _mm_and_si128(notZ[b], notZ[c]));
//	field_cp[6][b] = _mm_setzero_si128();
//	field_cp[6][c] = _mm_setzero_si128();
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[6][idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[6][idx] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[6][idx % 10] = _mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[b]), _mm_and_si128(notZ[c], notZ[a])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[b], notY[a])), bitZ[c]));
//	}
//	minArray[6] = bitCount(field_cp[6]);
//
//
//
//	//hit0 blow0
//	field_cp[7][a] = _mm_setzero_si128();
//	field_cp[7][b] = _mm_setzero_si128();
//	field_cp[7][c] = _mm_setzero_si128();
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[7][idx] = _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[7][idx] = _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[7][idx % 10] = _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), notY[c])), _mm_and_si128(_mm_and_si128(notZ[a], notZ[b]), notZ[c]));
//	}
//	minArray[7] = bitCount(field_cp[7]);
//
//
//
//	//hit0 blow1
//	field_cp[8][a] = _mm_setzero_si128();
//	field_cp[8][b] = _mm_and_si128(field[b], _mm_and_si128(_mm_and_si128(notY[a], notY[c]), _mm_and_si128(notZ[a], notZ[c])));
//	field_cp[8][c] = _mm_and_si128(field[c], _mm_and_si128(_mm_and_si128(notY[a], notY[b]), _mm_and_si128(notZ[a], notZ[b])));
//	//S��M�̊�
//	for (int idx = S + 1; idx < M; idx++) {
//		field_cp[8][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//	}
//	//M��L�̊�
//	for (int idx = M + 1; idx < L; idx++) {
//		field_cp[8][idx] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//	}
//	//L��S�̊�
//	for (int idx = L + 1; idx < S + 10; idx++) {
//		field_cp[8][idx % 10] = _mm_or_si128(_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[c]), _mm_and_si128(notZ[a], notZ[b])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[a], notY[c])), bitZ[b]))
//			, (_mm_or_si128(_mm_and_si128(_mm_and_si128(field[idx % 10], bitY[a]), _mm_and_si128(notZ[b], notZ[c])), _mm_and_si128(_mm_and_si128(field[idx % 10], _mm_and_si128(notY[b], notY[c])), bitZ[a]))));
//	}
//	minArray[8] = bitCount(field_cp[8]);
//
//	for (int i = 0; i < 9; i++) {
//		if (max < minArray[i]) {
//			max = minArray[i];
//		}
//		sum += minArray[i];
//	}
//	if (sum > 0 && sum - minArray[0] == 0) {
//		maxNum = -1;
//	}
//	else {
//		maxNum = max > 0 ? max : 1000; //0�̂Ƃ���1000�ɂ���
//	}
//	return;
//}
//
