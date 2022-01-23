#include <iostream>
#include <emmintrin.h>
#include <intrin.h>
#include <vector>
#include <algorithm>
#include <functional>

//自作
#include "Next.h"
#include "GameInfo.h"
#include "Common.h"
using namespace std;

//*************メインで使用************:

//720手保存したvectorを作成
vector<Next> makeVector() {
	vector<Next> nexts(720);
	int i = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (x == y) continue;
			for (int z = 0; z < 10; z++) {
				if (x == z || y == z) continue;
				nexts[i++] = Next(x, y, z);
			}
		}
	}
	return nexts;
}


//生きているかどうかを確認する
void setIsArrive(__m128i field[], vector<Next>& target) {
	//field[target[0]] の (9 - target[1]]) * 10 + (9 - target[2])番目
	//64以上なら 64ひいて次のptr

	uint64_t* ptr;
	int position;
	for (int idx = target.size() - 1; idx >= 0; idx--) {
		position = ((9 - target[idx].target[1]) * 10) + (9 - target[idx].target[2]);
		ptr = (uint64_t*)&field[target[idx].target[0]];

		if (position > 64) {
			target[idx].isArrive = ((ptr[0] >> (position - 64)) & 1);
		}
		else {
			target[idx].isArrive = ((ptr[1] >> position) & 1);
		}



	}
	return;
}

void makeTargetArray(vector<Next>& target)
{
	int i = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (x == y) continue;
			for (int z = 0; z < 10; z++) {
				if (x == z || y == z) continue;
				target[i++] = Next(x, y, z);
			}
		}
	}
	return;
}

//vectorの中身全てに最大値をセットさせる
void setMaxNum(vector<Next>& target)
{
	for (auto& elm : target) {
		elm.getMaxNum();
	}
}

//ソート用に関数を定義
bool operator<(const Next& left, const Next& right)
{
	return left.maxNum < right.maxNum;
}
bool operator>(const Next& left, const Next& right)
{
	return left.maxNum > right.maxNum;
}


//************クラス内で使用*************

//ビットカウント
int bitCount(__m128i bit[]) {

	return __popcnt64(_mm_cvtsi128_si64x(bit[0])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[0], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[1])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[1], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[2])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[2], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[3])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[3], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[4])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[4], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[5])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[5], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[6])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[6], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[7])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[7], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[8])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[8], 8)))
		+ __popcnt64(_mm_cvtsi128_si64x(bit[9])) + __popcnt64(_mm_cvtsi128_si64x(_mm_srli_si128(bit[9], 8)));
}