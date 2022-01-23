//#pragma once
//#include <emmintrin.h>
//#include <vector>
//class Target
//{
//
//	//フィールドコピー
//	__m128i field_cp[10];
//	std::vector<Target> target;
//
//public:
//	//フィールド
//	static __m128i* field;
//	static __m128i* bitY;
//	static __m128i* notY;
//	static __m128i* bitZ;
//	static __m128i* notZ;
//
//	//上位n件に絞るための候補値最大
//	int maxNum;
//	//3桁の答える数字
//	int target[3];
//
//	//// 次の手
//	//int nextTarget[3];
//
//	//コンストラクタ
//	Target();
//	Target(int first, int second, int third);
//
//	//9パターンの応答から可能性最大の手を探す(field_cpに変更を加える)
//	static void getMaxNum();
//
//	//1手先から最大手を選ぶ
//	static void nextTarget(); //並列でおこなう
//	int fullSearch(int pat);
//
//
//};