#pragma once
#include <emmintrin.h>

class GameInfo
{

	//選択した手
	int target[3];
	//hitBlow格納用
	int hb[2]; //2bit 2bitで4bitで表される
	//何手目か
	int turn;

	//bit計算用
	__m128i bitY[10];
	__m128i notY[10];
	__m128i bitZ[10];
	__m128i notZ[10];


public:
	//128bitの配列
	__m128i field[10];

	//テスト用初手
	int first[3];

	//答え
	int ans[3];

	//定数宣言
	const int RANGE = 720;
	const int LOOP = 10; //n回行う

	//コンストラクタ
	GameInfo();

	//***************初期設定******************
	//初期化
	void init();

	//フィールドをセット
	void setField();
	//フィールドをゲット
	__m128i* getField();
	__m128i* getBitY();
	__m128i* getNotY();
	__m128i* getBitZ();
	__m128i* getNotZ();

	//答えをランダムに選ぶ
	void setAnswer();

	//初手をランダムに選ぶ
	void setFirstTarget();


	//**************************************************


	//指定された手にセットする
	void setTarget(int arr[]);

	//指定されたHBにセットする
	void setHitBlow(int arr[]);

	//ランダムな3桁を作成
	void makeRandom(int arr[]);
	



	//*********:ゲーム終了判断*************:

	bool isEnd();

	//フィールドを更新する
	int updateField();

	//hit blow を確認する
	void hitBlow();

	//**************************************





	//**************表示系***
	
	//選択した手を表示
	void showTarget();
	//答えを表示
	void showAnswer();
	//hitblowを表示
	void showHitBlow();



	//**************統計用***********

	//配列
	int turnArray[10] = {}; //0で初期化構文?
	int optionArray[10] = {};

	//終了後処理
	void gameEnd();
};