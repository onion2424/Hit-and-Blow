#include <iostream>
#include <emmintrin.h>
#include <intrin.h>
#include <vector>
#include <algorithm>
#include <functional>

//����
#include "Next.h"
#include "GameInfo.h"

using namespace std;

void setIsArrive(__m128i field[], vector<Next>& target);
void makeTargetArray(vector<Next>& target); //720��Target�C���X�^���X���쐬����
void setMaxNum(vector<Next>& target);
bool operator<(const Next& left, const Next& right);  //sort�p
bool operator>(const Next& left, const Next& right);  //sort�p
vector<Next> makeVector(); //�A�h���X��Ԃ��������ǂ�?

//�r�b�g�J�E���g
int bitCount(__m128i bit[]);

//enum��`
typedef enum {
	pat3_0 = 0b1100,
	pat0_3 = 0b0011,
	pat1_2 = 0b0110,
	pat2_0 = 0b1000,
	pat1_1 = 0b0101,
	pat0_2 = 0b0010,
	pat1_0 = 0b0100,
	pat0_0 = 0b0000,
	pat0_1 = 0b0001
} Pattern;
