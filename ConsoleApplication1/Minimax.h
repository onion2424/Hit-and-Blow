#pragma once
#include <emmintrin.h>
#include <vector>
class MiniMax
{



public:
	//答えの可能性
	__m128i possible[10];

	//定数
	static __m128i* searchField;
	static __m128i* bitY;
	static __m128i* notY;
	static __m128i* bitZ;
	static __m128i* notZ;

	//上位n件に絞るための候補値最大
	int maxNum;

	//コンストラクタ
	MiniMax();

	//9パターンの応答から可能性最大の手を探す(fieldに変更を加える)
	void getMaxNum(int a, int b, int c);

};