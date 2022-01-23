#include "Next.h"
#include "Common.h"

#include <future>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
bool operator<(const MiniMax& left, const MiniMax& right);
bool operator>(const MiniMax& left, const MiniMax& right);

__m128i* Next::field;

//コンストラクタ（使わない）
Next::Next()
{

}

//全パターン作成するためのコンストラクタ
Next::Next(int first, int second, int third)
{
	target[0] = first;
	target[1] = second;
	target[2] = third;
	return;
}

void Next::getMaxNum() {
	//MaxNum, possibleが最小の時の情報に更新される
	memcpy(possible, field, sizeof(possible));
	MiniMax::getMaxNum(target[0], target[1], target[2]);
	return;
}

void Next::setNext() {
	const int size = mins.size();
	int min;
	if (size > 0) {
		//720こずつ用意しておく
		mins.reserve(size * 720 + size);
		
		for (int i = 0; i < size; i++) {
			MiniMax::searchField = mins[i].possible;
			setNext_step();
			//後ろ720を削除
			min = (*min_element(mins.begin(), mins.end())).maxNum;
			mins.erase(remove_if(mins.end() - 720, mins.end(), [min](MiniMax elm) { return elm.maxNum > min; }), mins.end());
		}
	}
	else {
		mins.reserve(720);
		MiniMax::searchField = possible;
		//memcpy(possible, field, sizeof(possible));
		setNext_step();
	}
	
	//最小値以外削除する
	min = (*min_element(mins.begin(), mins.end())).maxNum;
	mins.erase(remove_if(mins.begin(), mins.end(), [min](MiniMax elm) { return elm.maxNum > min; }), mins.end());
	maxNum = mins[0].maxNum;
	return;
}

void Next::setNext_step() {
	int i = 0;
	MiniMax min;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (x == y) continue;
			for (int z = 0; z < 10; z++) {
				if (x == z || y == z) continue;
				memcpy(min.possible, MiniMax::searchField, sizeof(min.possible));
				min.getMaxNum(x, y, z);
				mins.emplace_back(min);
			}
		}
	}
}

//ソート用に関数を定義
bool operator<(const MiniMax& left, const MiniMax& right)
{
	return left.maxNum < right.maxNum;
}
bool operator>(const MiniMax& left, const MiniMax& right)
{
	return left.maxNum > right.maxNum;
}