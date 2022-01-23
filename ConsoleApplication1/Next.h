#pragma once
#include "Minimax.h"
#include <vector>
#include <emmintrin.h>

class Next :
	public MiniMax
{
public:
	//現在のフィールドを保持
	static __m128i* field;
	//コンストラクタ
	Next(int first, int second, int third);
	Next();

	//次の手を保存
	int target[3];

	//生きているかどうか
	bool isArrive = true;

	//	次の手の最大手を格納
	std::vector<MiniMax> mins;


	//オーバーライド
	void getMaxNum();

	
	//	次の手を探す
	void setNext();
	void setNext_step();
};

