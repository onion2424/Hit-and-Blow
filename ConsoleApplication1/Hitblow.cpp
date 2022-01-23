// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include<string>
#include <iostream>
#include <emmintrin.h>
#include <intrin.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>

//自作
#include "Next.h"
#include "GameInfo.h"
#include "Common.h"


//関数宣言
bool isValidCall(std::string input, int call[3]);
bool isValidHB(std::string input, int hb[2]);

int main()
{
	int turn = 1; //何ターン目か
	int count = 0;

	std::string input = "";
	int call[3] = {}; //コールを分解して格納する
	int hb[2] = {}; //H&Bを分解して格納する

	//Targetインスタンス作成
	std::vector<Next> nexts;
	//次の手を選ぶための期待候補数最小値、最大値格納用
	int min = 0;
	int max = 0;

	std::cout << "終了する場合は 'q' を入力してください。" << std::endl;
	std::cout << "また、途中でやり直す場合は 'r' を入力してください。" << std::endl << std::endl;

	GameInfo gi; //ゲーム情報クラスのインスタンス
	gi.init();  //初期設定
	//staticメンバのアドレスを設定
	Next::field = gi.getField();
	MiniMax::bitY = gi.getBitY();
	MiniMax::notY = gi.getNotY();
	MiniMax::bitZ = gi.getBitZ();
	MiniMax::notZ = gi.getNotZ();

Game:
	while (true) {
		std::cout << turn << "ターン目" << std::endl;
		if (turn == 1) { //1ターン目ならゲームの情報を初期化する
			gi.setField();
		}

		//正しくコールが入力されるまで繰り返す(変数 : callに格納される)
		//callをゲーム情報にセットする
		while (std::cout << "コールした手を入力してください : ", std::cin >> input, !isValidCall(input, call)) {
			turn = input == "r" ? 1 : turn; //reset時はturnを１にすればいい
			if (input == "q") {
				return 0; //ゲーム終了
			}
			else if (input == "r") {
				std::cout << "リスタート" << std::endl << std::endl;
				goto Game; //ラベル付きcontinueの代わり
			}
		}
		gi.setTarget(call);


		//正しくH&Bが入力されるまで繰り返す (変数 : hbに格納される)
		//hbをゲーム情報にセットする
		while (std::cout << "Hit&Blowを '-' 繋ぎで入力してください : ", std::cin >> input, !isValidHB(input, hb)) {
			turn = input == "r" ? 1 : turn; //reset時はturnを１にすればいい
			if (input == "q") {
				return 0; //ゲーム終了
			}
			else if (input == "r") {
				std::cout << "リスタート" << std::endl << std::endl;
				goto Game; //ラベル付きcontinueの代わり
			}
		}
		if (input[0] == '3') { //3-0だった場合はリセット
			std::cout << "特定成功!!次の試合へ" << std::endl << std::endl;
			turn = 1;
			continue;
		}
		gi.setHitBlow(hb);


		//ゲーム情報の残りの候補数を更新する
		std::cout << "残り : " << (count = gi.updateField()) << "パターン" << std::endl;
		if (!count) { //残りが0になってしまったらやり直させる
			std::cout << "※答えが存在しません。もう一度やり直してください。" << std::endl << std::endl;
		}

		//720手の配列を作成する（実体コピーでも良い）
		//その後全手の期待候補数を調べそのうちの最大値をセットする
		nexts = makeVector();
		setMaxNum(nexts);

		//最小値以外を削除する
		min = (*min_element(nexts.begin(), nexts.end())).maxNum;
		nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());
		//最大値が被るときは次の手をみる
		while (nexts[0].maxNum > 1) {
			for (int i = 0; i < nexts.size(); i++) {
				//一手進める
				nexts[i].setNext();

			}
			//	最小値以外を削除する
			min = (*min_element(nexts.begin(), nexts.end())).maxNum;
			max = (*max_element(nexts.begin(), nexts.end())).maxNum;
			if (min == max) break; //最小値と最大値が変わらないときはそれ以上見ても無意味なので抜ける
			nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());
		}
		//候補を出力する
		std::cout << "コール手の候補(〇は正解の可能性が残っているコール) : ";
		setIsArrive(gi.getField(), nexts);
		for (int i = 0; i < nexts.size(); i++) { //面倒なのでsizeを変数に入れずに使う
			if (i % 10 == 0) std::cout << std::endl; //10桁毎に改行
			std::cout << nexts[i].target[0] << nexts[i].target[1] << nexts[i].target[2] << (nexts[i].isArrive ? "〇" : "　") << " ";

		}

		//メモリ解放
		nexts.shrink_to_fit();

		//ターンを進める
		turn++;
		std::cout << std::endl << std::endl;
	}
	return 0;
}

bool isValidCall(std::string input, int call[3]) {
	bool ret = false;
	//数値かどうかをチェックする
	if (input.length() == 3 && std::all_of(input.cbegin(), input.cend(), isdigit))
	{
		//vectorに入れて重複チェック
		std::vector<int> numbers = { input[0] - '0', input[1] - '0' , input[2] - '0' };
		std::sort(numbers.begin(), numbers.end());
		numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());

		//sizeが変わらなければ重複なしと判断
		if (numbers.size() == 3) {
			call[0] = input[0] - '0';
			call[1] = input[1] - '0';
			call[2] = input[2] - '0';
			ret = true;
		}
		else {
			std::cout << "※数字が重複しています。" << std::endl;
		}
	}
	else {
		std::cout << "※3桁被りなしの数値を入力してください。" << std::endl;
	}

	return ret;
}

bool isValidHB(std::string input, int hb[2]) {
	bool ret = false;
	//2文字目を0にして数値かどうかチェック→足して3以下であることを確認
	input[1] = '0';
	if (input.length() == 3 && std::all_of(input.cbegin(), input.cend(), isdigit) && input[0] - '0' + input[2] - '0' <= 3)
	{
		hb[0] = input[0] - '0';
		hb[1] = input[2] - '0';
		ret = true;
	}
	else {
		std::cout << "※正しいHit Blow数を入力してください。" << std::endl;
	}
	return ret;
}
