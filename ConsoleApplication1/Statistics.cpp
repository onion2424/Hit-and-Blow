// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

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

int _main()
{
	//カウント用
	int cnt;

	//インスタンス化と同時に初期設定を行う
	GameInfo gi;

	//初期設定
	gi.init();

	//staticメンバのアドレスを設定
	Next::field = gi.getField();
	MiniMax::bitY = gi.getBitY();
	MiniMax::notY = gi.getNotY();
	MiniMax::bitZ = gi.getBitZ();
	MiniMax::notZ = gi.getNotZ();

	//Targetインスタンス作成
	vector<Next> nexts;
	int min = 0;
	int max = 0;
	//makeTargetArray(target);

	//************ゲーム開始***************　複数回の場合はここからループすればいい

	for (int n = 0; n < gi.LOOP; n++) { //n回の統計を取る
#pragma region init
		//フィールドをセットする
		gi.setField();


		//答えをランダムに選ぶ
		gi.setAnswer();
		//gi.showAnswer(); //表示する

		//1手目をランダムで選ぶ
		gi.setFirstTarget();
		//gi.showTarget();

		//カウントを初期化
		cnt = 1;

#pragma endregion 

		//++++++++++ループ部分++++++++++
		while (!gi.isEnd()) { //ここでhitBlowがセットされる
			//gi.showHitBlow();

			// 1. フィールドを更新する(残りの数を保存する)
			gi.optionArray[cnt - 1] += gi.updateField();
			//cout << "残り : " << gi.updateField() << endl;

			nexts = makeVector();
			setMaxNum(nexts);

			//最小値以外を削除する
			min = (*min_element(nexts.begin(), nexts.end())).maxNum;
			nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());

			while (nexts[0].maxNum > 1) {
				for (int i = 0; i < nexts.size(); i++) {
					//一手進める
					nexts[i].setNext();

				}
				//	最小値以外を削除する
				min = (*min_element(nexts.begin(), nexts.end())).maxNum;
				max = (*max_element(nexts.begin(), nexts.end())).maxNum;
				if (min == max) break;
				nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());
			}

			//最上位を次の手にセットする
			gi.setTarget(nexts[0].target);

			//メモリ解放
			nexts.shrink_to_fit();

			//表示する
			//gi.showTarget();

			if (cnt++ > 10) {
				break;
			}

		}


		//何回目かを格納する
		gi.turnArray[cnt - 1]++;

	}
	//ゲーム終了時処理
	gi.gameEnd();
	return 0;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
