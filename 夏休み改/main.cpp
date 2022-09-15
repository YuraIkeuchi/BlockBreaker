#include "DxLib.h"

const char TITLE[] = "K020G1233池内由良：評価課題2";

const int WIN_WIDTH = 1000; //ウィンドウ横幅
const int WIN_HEIGHT = 800;//ウィンドウ縦幅


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0xFF);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み



	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	//スタート画面
	int titleX = 0;
	int titleY = 0;
	int title;
	title = LoadGraph("TITLE.png");
	int Title[32] = { 0 };
	LoadDivGraph("TITLE2.png", 31, 31, 1, 1000, 800, Title);
	int TITLETIMER = 0;
	//セレクト画面
	int selectX = 0;
	int selectY = 0;
	int select[2] = { 0 };
	LoadDivGraph("SELECT.png", 2, 2, 1, 1000, 800, select);
	int selectTime = 0;
	//背景
	int backX = 0;
	int backY = 0;
	int back[2];
	back[0] = LoadGraph("back.png");
	back[1] = LoadGraph("back2.png");

	//	ゲームオーバー画面
	int gameover[10] = { 0 };
	LoadDivGraph("gameover11.png", 10, 10, 1, 1000, 800, gameover);
	int count = 0;
	int gameover2[4] = { 0 };
	LoadDivGraph("gameover2.png", 4, 4, 1, 1000, 200, gameover2);
	int gameoverTime2 = 0;
	int gameoverX = 0;
	int gameoverY = 0;
	int gameover2X = 0;
	int gameover2Y = 500;
	int SELECT2;
	SELECT2 = LoadGraph("SELECT2.png");
	int SELECT2X = 0;
	int SELECT2Y = 600;
	//エンドロール画面
	int ED;
	ED = LoadGraph("ED.png");
	int EDX = 0;
	int EDY = 0;
	//ブロック
	int blockX = 64;
	int blockY = 32;
	int block[5];
	block[0] = LoadGraph("block.png");
	block[1] = LoadGraph("block2.png");
	block[2] = LoadGraph("block3.png");
	block[3] = LoadGraph("block4.png");
	block[4] = LoadGraph("block5.png");

	int blockR = 32;
	int blockR2 = 16;
	int blockflag[9][6] = { 0 };

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			blockflag[i][j] = 1;
		}
	}

	int blockflag2[9][10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			blockflag2[4][1] = 1;
			blockflag2[5][1] = 1;
			blockflag2[3][2] = 1;
			blockflag2[4][2] = 1;
			blockflag2[5][2] = 1;
			blockflag2[6][2] = 1;
			blockflag2[2][3] = 1;
			blockflag2[3][3] = 1;
			blockflag2[4][3] = 1;
			blockflag2[5][3] = 1;
			blockflag2[6][3] = 1;
			blockflag2[7][3] = 1;
			blockflag2[1][4] = 1;
			blockflag2[2][4] = 1;
			blockflag2[3][4] = 1;
			blockflag2[4][4] = 1;
			blockflag2[5][4] = 1;
			blockflag2[6][4] = 1;
			blockflag2[7][4] = 1;
			blockflag2[8][4] = 1;
			blockflag2[1][5] = 1;
			blockflag2[2][5] = 1;
			blockflag2[3][5] = 1;
			blockflag2[4][5] = 1;
			blockflag2[5][5] = 1;
			blockflag2[6][5] = 1;
			blockflag2[7][5] = 1;
			blockflag2[8][5] = 1;
			blockflag2[2][6] = 1;
			blockflag2[3][6] = 1;
			blockflag2[4][6] = 1;
			blockflag2[5][6] = 1;
			blockflag2[6][6] = 1;
			blockflag2[7][6] = 1;
			blockflag2[2][7] = 1;
			blockflag2[3][7] = 1;
			blockflag2[4][7] = 1;
			blockflag2[5][7] = 1;
			blockflag2[6][7] = 1;
			blockflag2[7][7] = 1;
			blockflag2[1][8] = 1;
			blockflag2[4][8] = 1;
			blockflag2[5][8] = 1;
			blockflag2[8][8] = 1;
			blockflag2[4][9] = 1;
			blockflag2[5][9] = 1;
		}
	}
	int EF[7] = { 0 };
	LoadDivGraph("EF.png", 6, 6, 1, 128, 128, EF);
	int EF2[7] = { 0 };
	LoadDivGraph("EF2.png", 6, 6, 1, 128, 128, EF2);
	int EF3[7] = { 0 };
	LoadDivGraph("EF3.png", 6, 6, 1, 128, 128, EF3);
	int EF4[7] = { 0 };
	LoadDivGraph("EF4.png", 6, 6, 1, 128, 128, EF4);
	int EF5[7] = { 0 };
	LoadDivGraph("EF5.png", 6, 6, 1, 128, 128, EF5);
	int EFtimer[9][6] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			EFtimer[i][j] = 0;
		}
	}
	int EFflag[9][6] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			EFflag[i][j] = 0;
		}
	}

	int EFflag2[9][10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			EFflag2[4][1] = 0;
			EFflag2[5][1] = 0;
			EFflag2[3][2] = 0;
			EFflag2[4][2] = 0;
			EFflag2[5][2] = 0;
			EFflag2[6][2] = 0;
			EFflag2[2][3] = 0;
			EFflag2[3][3] = 0;
			EFflag2[4][3] = 0;
			EFflag2[5][3] = 0;
			EFflag2[6][3] = 0;
			EFflag2[7][3] = 0;
			EFflag2[1][4] = 0;
			EFflag2[2][4] = 0;
			EFflag2[3][4] = 0;
			EFflag2[4][4] = 0;
			EFflag2[5][4] = 0;
			EFflag2[6][4] = 0;
			EFflag2[7][4] = 0;
			EFflag2[8][4] = 0;
			EFflag2[1][5] = 0;
			EFflag2[2][5] = 0;
			EFflag2[3][5] = 0;
			EFflag2[4][5] = 0;
			EFflag2[5][5] = 0;
			EFflag2[6][5] = 0;
			EFflag2[7][5] = 0;
			EFflag2[8][5] = 0;
			EFflag2[2][6] = 0;
			EFflag2[3][6] = 0;
			EFflag2[4][6] = 0;
			EFflag2[5][6] = 0;
			EFflag2[6][6] = 0;
			EFflag2[7][6] = 0;
			EFflag2[2][7] = 0;
			EFflag2[3][7] = 0;
			EFflag2[4][7] = 0;
			EFflag2[5][7] = 0;
			EFflag2[6][7] = 0;
			EFflag2[7][7] = 0;
			EFflag2[2][8] = 0;
			EFflag2[4][8] = 0;
			EFflag2[5][8] = 0;
			EFflag2[8][8] = 0;
			EFflag2[4][9] = 0;
			EFflag2[5][9] = 0;
		}
	}

	int EFtimer2[9][10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			EFtimer2[i][j] = 0;
		}
	}
	int EFX = 0;
	int EFY = 0;
	int EFR = 36;
	int EFR2 = 35;
	//プレイヤー
	int playerX = 300;
	int playerY = 700;;
	int playerR = 64;
	int playerR2 = 32;
	int player[6];
	LoadDivGraph("player2.png", 6, 6, 1, 64, 32, player);
	int playerTimer = 0;
	int playerflag = 0;
	//HP
	int HP = 3;
	int HP2 = 1;
	int HPX = 645;
	int HPY = 470;
	int HPgh[3];
	HPgh[0] = LoadGraph("HP.png");
	HPgh[1] = LoadGraph("HP2.png");
	HPgh[2] = LoadGraph("HP3.png");
	//スコア
	int score = 0;
	//SP
	int SP;
	SP = LoadGraph("SP.png");
	int SPX = 290;
	int SPY = 200;;
	int SPR = 16;
	int SPR2 = 16;
	int SPflag = 0;
	int SPcount = 1500;
	//弾
	int bollX = 200;
	int bollY = 300;
	int bollX2 = 150;
	int bollY2 = 300;
	int speed = 5;
	int speed2 = 5;
	int boll;
	boll = LoadGraph("boll.png");
	int bolldead[7] = { 0 };
	LoadDivGraph("bolldead2.png", 7, 7, 1, 128, 128, bolldead);
	int bolldeadTimer = 0;
	int deadflag = 0;
	int bolldeadX = 0;
	int bolldeadY = 720;
	int deadcount = 0;
	int bollTimer = 120;
	int bollflag = 1;
	int FireX = 0;
	int FireY = 0;
	int fireflag = 0;
	int fireTimer = 0;
	int Fire[5] = { 0 };
	LoadDivGraph("Fire.png", 5, 5, 1, 32, 32, Fire);
	int color = GetColor(255, 255, 255);
	//音楽
	int SEHandle[2];
	SEHandle[0] = LoadSoundMem("ブロック崩し.mp3");
	SEHandle[1] = LoadSoundMem("ブロック崩し_2.mp3");
	int EDS;
	EDS = LoadSoundMem("8bit-Epilogue01.mp3");
	int TopPositionFlag = 0;
	int OPS;
	OPS = LoadSoundMem("bgm_maoudamashii_8bit26.mp3");
	int OPSFlag = 0;
	//シーン
	int scene = 0;
	//スコア用の数字
	int number = 1234567890;
	int graphHandle[11];
	LoadDivGraph("number2.png", 10, 10, 1, 128, 128, graphHandle);
	int ghIndex;
	//角度
	int angle = 0;
	//文字の配列
	char strNum[11];
	int point = 49;
	int point2 = 49;
	int point3 = 49;
	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理

		//スコアの表示

		//シーン0
		if (scene == 0)
		{
			if (TITLETIMER <= 160)
			{
				TITLETIMER++;
			}
			if (CheckSoundMem(OPS == 0)) 
			{
				ChangeVolumeSoundMem(170 * 80 / 100, OPS);
				PlaySoundMem(OPS, DX_PLAYTYPE_LOOP, TopPositionFlag = 0);
			}
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 1;
			}
		}
		//シーン1
		else if (scene == 1)
		{
			if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0)
			{
				selectTime = 1;
			}

			if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0)
			{
				selectTime = 0;
			}

			if (selectTime == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 2;
				StopSoundMem(OPS);
			}

			else if (selectTime == 1 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 3;
				StopSoundMem(OPS);
			}
		}
		//シーン2
		else if (scene == 2)
		{
			//プレイヤーの移動
			if (keys[KEY_INPUT_RIGHT] == 1)
			{
				playerX = playerX + 8;
			}

			if (keys[KEY_INPUT_LEFT] == 1)
			{
				playerX = playerX - 8;
			}

			//バーの移動制限距離

			if (playerflag == 0)
			{
				if (playerX >= 550)
				{
					playerX = 550;
				}

				if (playerX <= 90)
				{
					playerX = 90;
				}
			}

			else if (playerflag == 1)
			{
				if (playerX >= 540)
				{
					playerX = 540;
				}

				if (playerX <= 100)
				{
					playerX = 100;
				}
			}
			//スコア表示
			if (point <= 39)
			{
				point = 49;
				point2 = point2 - 1;
			}
			if (point2 <= 39)
			{
				point2 = 49;
				point3 = point3 - 1;
			}
			//弾の処理
			bollX += speed;
			bollY += speed2;

			if (bollX >= 555 && bollflag == 1 && HP != 0)
			{
				speed = speed * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (bollX <= 50 && bollflag == 1 && HP != 0)
			{
				speed = speed * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (bollY <= 50 && bollflag == 1 && HP != 0)
			{
				speed2 = speed2 * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (HP != 0 && bollY >= 800 && bollflag == 1)
			{
				bollflag = 0;
				HP = HP - 1;
				speed = 0;
			}

			if (HP == 2 && playerTimer <= 148 && bollflag == 0)
			{
				deadcount = 1;
				playerTimer++;
			}

			else if (HP == 1 && playerTimer <= 200 && bollflag == 0)
			{	
				deadcount = 2;
				playerTimer++;
			}

			if (deadcount == 1 && bollflag == 0)
			{
				deadflag = 1;
				bolldeadTimer++;
				bolldeadX = bollX - 20;

				if (bolldeadTimer == 35)
				{
					bolldeadTimer = 0;
					deadcount == 0;
				}
			}

			else if (deadcount == 2 && bollflag == 0)
			{
				deadflag = 1;
				bolldeadTimer++;
				bolldeadX = bollX - 20;
				if (bolldeadTimer == 35)
				{
					bolldeadTimer = 0;
					deadcount == 0;
				}
			}

			//ボールとバーの角度の調整
			if (playerX > bollX)
			{
				angle = playerX - bollX;
			}

			else if (playerX < bollX)
			{
				angle = bollX - playerX;
			}
			//バーとの当たり判定
			if (bollX > playerX - playerR && bollX < playerX + playerR - 15 && playerY == bollY + 20 && bollflag == 1 && HP != 0)
			{
				speed2 = speed2 * -1.1;

				if (speed <= 7 || speed >= -7)
				{
					if (angle >= 1 && angle <= 16)
					{
						speed = speed * -1 - 2;
					}

					else if (angle >= 17 && angle <= 32)
					{
						speed = speed * -1 - 1;
					}

					else if (angle >= 33 && angle <= 48)
					{
						speed = speed * -1 + 1;
					}

					else if (angle > 49)
					{
						speed = speed * -1 + 2;
					}
				}
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
				PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
			}

			//玉のエフェクト
			if (speed >= 7 || speed <= -7)
			{
				fireflag = 1;
			}

			else
			{
				fireflag = 0;
			}

			if (fireflag == 1)
			{
				FireX = bollX;
				FireY = bollY;
				fireTimer++;
			}

			if (fireTimer == 5)
			{
				fireTimer = 1;
			}

			else if (fireflag == 0)
			{
				fireTimer = 0;
			}
			//ブロックの当たり判定
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 6; j++) {
					if (bollY > blockY * j)
					{
						if (blockflag[i][j] == 1 && bollY - 2 <= j * blockY + blockR2 + 40 && bollX >= i * blockX - blockR + 20 && bollX <= i * blockX + blockR + 20)
						{
							blockflag[i][j] = 0;
							speed2 = speed2 * -1.1;
							ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
							PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
							score = score + 20;
							point = point - 2;
						}
					}

					else if (bollY < j * blockY)
					{
						if (blockflag[i][j] == 1 && bollY + 2 >= j * blockY - blockR2 - 40&& bollX >= i * blockX + blockR + 20 && bollX <= i * blockX + blockR + 20)
						{
							blockflag[i][j] = 0;
							speed2 = speed2 * -1.1;
							ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
							PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
							score = score + 20;
							point = point - 2;
						}
					}

					
						if (bollX > i * blockX - blockR)
						{
							if (blockflag[i][j] == 1 && bollY <= j * blockY + blockR2 + 30 && bollY >= j * blockY - blockR2 + 30 && bollX <= i * blockX - blockR + 20)
							{
								blockflag[i][j] = 0;
								speed = speed * -1.1;
								ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
								PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
								score = score + 20;
								point = point - 2;
							}
						}

						else if (bollX < i * blockX + blockR)
						{
							if (blockflag[i][j] == 1 && bollY <= j * blockY + blockR2 + 30 && bollY >= j * blockY - blockR2 + 30 && bollX >= i * blockX + blockR + 20)
							{
								blockflag[i][j] = 0;
								speed = speed * -1.1;
								ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
								PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
								score = score + 20;
								point = point - 2;
							}
						}
				
					//エフェクトの処理
					if (blockflag[i][j] == 0)
					{
						EFX = blockX;
						EFY = blockY;
						EFflag[i][j] = 1;
					}

					if (EFflag[i][j] == 1)
					{
						if (EFtimer[i][j] >= 0 && EFtimer[i][j] <= 6)
						{
							EFtimer[i][j]++;
						}
					}
					if (EFtimer[i][j] == 7)
					{
						EFflag[i][j] = 0;
					}
				}
			}

			//ボール復活タイマー
			if (bollflag == 0)
			{
				bollTimer = bollTimer - 1;
				if (bollTimer <= 0)
				{
					deadflag = 0;
					bolldeadTimer = 0;
					bollflag = 1;
					bollTimer = 120;
					bollX = 200;
					bollY = 300;
					speed = 5;
					speed2 = 5;
				}
			}

			//スペシャルアイテム
			if (blockflag[4][5] == 0)
			{
				SPflag = 1;
			}

			if (SPflag == 1)
			{
				SPY = SPY + 2;
			}

			if (SPX > playerX - playerR && SPX < playerX + playerR && playerY == SPY + 20 && SPflag == 1 &&  HP != 0)
			{
				SPflag = 0;
				playerR = playerR + 30;
				playerflag = 1;
				SPcount = 1500;
			}

			if (playerR > 64)
			{
				SPcount = SPcount - 1;
			}
			if (SPcount <= 0)
			{
				playerR = playerR - 30;
				SPcount = 1500;
				playerflag = 0;
			}

			//シーン4へ
			if (HP == 0)
			{
				scene = 4;
			}

			//シーン5へ
			if (score >= 800)
			{
				scene = 5;
			}
		}
		//シーン3
		else if (scene == 3)
		{
			//ハードのため幅縮小
			playerR = 40;
			//玉の初期値変更
			//プレイヤーの移動処理
			if (keys[KEY_INPUT_RIGHT] == 1)
			{
				playerX = playerX + 8;
			}

			if (keys[KEY_INPUT_LEFT] == 1)
			{
				playerX = playerX - 8;
			}

			//バーの移動制限距離
			if (playerflag == 0)
			{
				if (playerX >= 560)
				{
					playerX = 560;
				}

				if (playerX <= 80)
				{
					playerX = 80;
				}
			}

			else if (playerflag == 1)
			{
				if (playerX >= 540)
				{
					playerX = 540;
				}

				if (playerX <= 100)
				{
					playerX = 100;
				}
			}
			//スコア表示
			if (point <= 39)
			{
				point = 49;
				point2 = point2 - 1;
			}
			if (point2 <= 39)
			{
				point2 = 49;
				point3 = point3 - 1;
			}
			//弾の処理
			bollX2 += speed;
			bollY2 += speed2;

			if (bollX2 >= 555 && bollflag == 1 && HP != 0)
			{
				speed = speed * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (bollX2 <= 50 && bollflag == 1 && HP != 0)
			{
				speed = speed * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (bollY2 <= 50 && bollflag == 1 && HP != 0)
			{
				speed2 = speed2 * -1;
				ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[0]);
				PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			}

			if (HP != 0 && bollY2 >= 800 && bollflag == 1)
			{
				bollflag = 0;
				HP2 = HP2 - 1;
			}

			//ボールとバーの角度の調整
			if (playerX > bollX2)
			{
				angle = playerX - bollX2;
			}

			else if (playerX < bollX2)
			{
				angle = bollX2 - playerX;
			}
			//バーとの当たり判定
			if (bollX2 > playerX - playerR && bollX2 < playerX + playerR - 15 && playerY == bollY2 + 20 && bollflag == 1 && HP != 0)
			{
				speed2 = speed2 * -1.1;

				if (speed <= 7 || speed >= -7)
				{
					if (angle >= 1 && angle <= 10)
					{
						speed = speed * -1 - 2;
					}

					else if (angle >= 11 && angle <= 20)
					{
						speed = speed * -1 - 1;
					}

					else if (angle >= 21 && angle <= 30)
					{
						speed = speed * -1 + 1;
					}

					else if (angle > 31)
					{
						speed = speed * -1 + 2;
					}
				}
				PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
			}

		//玉のエフェクト
			if (speed >= 7 || speed <= -7)
			{
				fireflag = 1;
			}

			else
			{
				fireflag = 0;
			}

			if (fireflag == 1)
			{
				FireX = bollX2;
				FireY = bollY2;
				fireTimer++;
			}

			if (fireTimer == 5)
			{
				fireTimer = 1;
			}

			else if (fireflag == 0)
			{
				fireTimer = 0;
			}

			//ブロックの当たり判定
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 10; j++) {
					if (bollY2 > j * blockY)
					{
						if (blockflag2[i][j] == 1 && bollY2 - 2 <= j * blockY + blockR2 + 35 && bollX2 >= i * blockX - blockR + 20 && bollX2 <= i * blockX + blockR + 20)
						{
							blockflag2[i][j] = 0;
							speed2 = speed2 * -1.1;
							ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
							PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
							score = score + 20;
							point = point - 2;
						}
					}

					else if (bollY2 < j * blockY)
					{
						if (blockflag2[i][j] == 1 && bollY2 + 2 >= j * blockY - blockR2 + 35 && bollX2 >= i * blockX + blockR + 15 && bollX2 <= i * blockX + blockR + 20)
						{
							blockflag2[i][j] = 0;
							speed2 = speed2 * -1.1;
							ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
							PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
							score = score + 20;
							point = point - 2;
						}
					}

				
						if (bollX2 > i * blockX - blockR)
						{
							if (blockflag2[i][j] == 1 && bollY2 <= j * blockY + blockR2 + 30 && bollY2 >= j * blockY - blockR2 + 30 && bollX2 <= i * blockX - blockR + 20)
							{
								blockflag2[i][j] = 0;
								speed = speed * -1.1;
								ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
								PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
								score = score + 20;
								point = point - 2;
							}
						}

						else if (bollX2 < i * blockX + blockR)
						{
							if (blockflag2[i][j] == 1 && bollY2 <= j * blockY + blockR2 + 30 && bollY2 >= j * blockY - blockR2 + 30 && bollX2 >= i * blockX + blockR + 20)
							{
								blockflag2[i][j] = 0;
								speed = speed * -1.1;
								ChangeVolumeSoundMem(170 * 80 / 100, SEHandle[1]);
								PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
								score = score + 20;
								point = point - 2;
							}
						}
					

					//エフェクトの処理
					if (blockflag2[4][1] == 0)
					{
						EFflag2[4][1] = 1;
					}

					if (blockflag2[5][1] == 0)
					{
						EFflag2[5][1] = 1;
					}

					if (blockflag2[3][2] == 0)
					{
						EFflag2[3][2] = 1;
					}

					if (blockflag2[4][2] == 0)
					{
						EFflag2[4][2] = 1;
					}

					if (blockflag2[5][2] == 0)
					{
						EFflag2[5][2] = 1;
					}

					if (blockflag2[6][2] == 0)
					{
						EFflag2[6][2] = 1;
					}

					if (blockflag2[2][3] == 0)
					{
						EFflag2[2][3] = 1;
					}

					if (blockflag2[3][3] == 0)
					{
						EFflag2[3][3] = 1;
					}

					if (blockflag2[4][3] == 0)
					{
						EFflag2[4][3] = 1;
					}

					if (blockflag2[5][3] == 0)
					{
						EFflag2[5][3] = 1;
					}

					if (blockflag2[6][3] == 0)
					{
						EFflag2[6][3] = 1;
					}

					if (blockflag2[7][3] == 0)
					{
						EFflag2[7][3] = 1;
					}

					if (blockflag2[1][4] == 0)
					{
						EFflag2[1][4] = 1;
					}

					if (blockflag2[2][4] == 0)
					{
						EFflag2[2][4] = 1;
					}

					if (blockflag2[3][4] == 0)
					{
						EFflag2[3][4] = 1;
					}

					if (blockflag2[4][4] == 0)
					{
						EFflag2[4][4] = 1;
					}

					if (blockflag2[5][4] == 0)
					{
						EFflag2[5][4] = 1;
					}

					if (blockflag2[6][4] == 0)
					{
						EFflag2[6][4] = 1;
					}

					if (blockflag2[7][4] == 0)
					{
						EFflag2[7][4] = 1;
					}

					if (blockflag2[8][4] == 0)
					{
						EFflag2[8][4] = 1;
					}

					if (blockflag2[1][5] == 0)
					{
						EFflag2[1][5] = 1;
					}

					if (blockflag2[2][5] == 0)
					{
						EFflag2[2][5] = 1;
					}

					if (blockflag2[3][5] == 0)
					{
						EFflag2[3][5] = 1;
					}

					if (blockflag2[4][5] == 0)
					{
						EFflag2[4][5] = 1;
					}

					if (blockflag2[5][5] == 0)
					{
						EFflag2[5][5] = 1;
					}

					if (blockflag2[6][5] == 0)
					{
						EFflag2[6][5] = 1;
					}

					if (blockflag2[7][5] == 0)
					{
						EFflag2[7][5] = 1;
					}

					if (blockflag2[8][5] == 0)
					{
						EFflag2[8][5] = 1;
					}

					if (blockflag2[2][6] == 0)
					{
						EFflag2[2][6] = 1;
					}

					if (blockflag2[3][6] == 0)
					{
						EFflag2[3][6] = 1;
					}

					if (blockflag2[4][6] == 0)
					{
						EFflag2[4][6] = 1;
					}

					if (blockflag2[5][6] == 0)
					{
						EFflag2[5][6] = 1;
					}

					if (blockflag2[6][6] == 0)
					{
						EFflag2[6][6] = 1;
					}

					if (blockflag2[7][6] == 0)
					{
						EFflag2[7][6] = 1;
					}

					if (blockflag2[2][7] == 0)
					{
						EFflag2[2][7] = 1;
					}

					if (blockflag2[3][7] == 0)
					{
						EFflag2[3][7] = 1;
					}

					if (blockflag2[4][7] == 0)
					{
						EFflag2[4][7] = 1;
					}

					if (blockflag2[5][7] == 0)
					{
						EFflag2[5][7] = 1;
					}

					if (blockflag2[6][7] == 0)
					{
						EFflag2[6][7] = 1;
					}

					if (blockflag2[7][7] == 0)
					{
						EFflag2[7][7] = 1;
					}

					if (blockflag2[1][8] == 0)
					{
						EFflag2[1][8] = 1;
					}

					if (blockflag2[4][8] == 0)
					{
						EFflag2[4][8] = 1;
					}

					if (blockflag2[5][8] == 0)
					{
						EFflag2[5][8] = 1;
					}

					if (blockflag2[8][8] == 0)
					{
						EFflag2[8][8] = 1;
					}

					if (blockflag2[4][9] == 0)
					{
						EFflag2[4][9] = 1;
					}

					if (blockflag2[5][9] == 0)
					{
						EFflag2[5][9] = 1;
					}

					if (EFflag2[i][j] == 1)
					{
						EFX = blockX;
						EFY = blockY;
						if (EFtimer2[i][j] >= 0 && EFtimer2[i][j] <= 6)
						{
							EFtimer2[i][j]++;
						}
					}
					if (EFtimer2[i][j] == 7)
					{
						EFflag2[i][j] = 0;
					}
				}
			}

			//ボール復活タイマー
			if (bollflag == 0)
			{
				bollTimer = bollTimer - 1;
				if (bollTimer <= 0)
				{
					bollflag = 1;
					bollTimer = 120;
					bollX2 = 150;
					bollY2 = 300;
					speed = 5;
					speed2 = 5;
				}
			}

			//シーン4へ
			if (HP2 == 0)
			{
				scene = 4;
			}

			//シーン5へ
			if (score >= 920)
			{
				scene = 5;
			}
		}
		//シーン4
		else if (scene == 4)
		{
			count++;
			if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0)
			{
				gameoverTime2 = 2;
			}

			if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0)
			{
				gameoverTime2 = 0;
			}

			if (gameoverTime2 == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
				HP = 3;
				HP2 = 1;
				blockflag[8][6];
				for (int i = 1; i < 9; i++)
				{
					for (int j = 1; j < 6; j++)
					{
						blockflag[i][j] = 1;
					}
				}

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						EFtimer[i][j] = 0;
					}
				}

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						EFtimer2[i][j] = 0;
					}
				}

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						blockflag2[4][1] = 1;
						blockflag2[5][1] = 1;
						blockflag2[3][2] = 1;
						blockflag2[4][2] = 1;
						blockflag2[5][2] = 1;
						blockflag2[6][2] = 1;
						blockflag2[2][3] = 1;
						blockflag2[3][3] = 1;
						blockflag2[4][3] = 1;
						blockflag2[5][3] = 1;
						blockflag2[6][3] = 1;
						blockflag2[7][3] = 1;
						blockflag2[1][4] = 1;
						blockflag2[2][4] = 1;
						blockflag2[3][4] = 1;
						blockflag2[4][4] = 1;
						blockflag2[5][4] = 1;
						blockflag2[6][4] = 1;
						blockflag2[7][4] = 1;
						blockflag2[8][4] = 1;
						blockflag2[1][5] = 1;
						blockflag2[2][5] = 1;
						blockflag2[3][5] = 1;
						blockflag2[4][5] = 1;
						blockflag2[5][5] = 1;
						blockflag2[6][5] = 1;
						blockflag2[7][5] = 1;
						blockflag2[8][5] = 1;
						blockflag2[2][6] = 1;
						blockflag2[3][6] = 1;
						blockflag2[4][6] = 1;
						blockflag2[5][6] = 1;
						blockflag2[6][6] = 1;
						blockflag2[7][6] = 1;
						blockflag2[2][7] = 1;
						blockflag2[3][7] = 1;
						blockflag2[4][7] = 1;
						blockflag2[5][7] = 1;
						blockflag2[6][7] = 1;
						blockflag2[7][7] = 1;
						blockflag2[1][8] = 1;
						blockflag2[4][8] = 1;
						blockflag2[5][8] = 1;
						blockflag2[8][8] = 1;
						blockflag2[4][9] = 1;
						blockflag2[5][9] = 1;
					}
				}

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						EFflag2[4][1] = 0;
						EFflag2[5][1] = 0;
						EFflag2[3][2] = 0;
						EFflag2[4][2] = 0;
						EFflag2[5][2] = 0;
						EFflag2[6][2] = 0;
						EFflag2[2][3] = 0;
						EFflag2[3][3] = 0;
						EFflag2[4][3] = 0;
						EFflag2[5][3] = 0;
						EFflag2[6][3] = 0;
						EFflag2[7][3] = 0;
						EFflag2[1][4] = 0;
						EFflag2[2][4] = 0;
						EFflag2[3][4] = 0;
						EFflag2[4][4] = 0;
						EFflag2[5][4] = 0;
						EFflag2[6][4] = 0;
						EFflag2[7][4] = 0;
						EFflag2[8][4] = 0;
						EFflag2[1][5] = 0;
						EFflag2[2][5] = 0;
						EFflag2[3][5] = 0;
						EFflag2[4][5] = 0;
						EFflag2[5][5] = 0;
						EFflag2[6][5] = 0;
						EFflag2[7][5] = 0;
						EFflag2[8][5] = 0;
						EFflag2[2][6] = 0;
						EFflag2[3][6] = 0;
						EFflag2[4][6] = 0;
						EFflag2[5][6] = 0;
						EFflag2[6][6] = 0;
						EFflag2[7][6] = 0;
						EFflag2[2][7] = 0;
						EFflag2[3][7] = 0;
						EFflag2[4][7] = 0;
						EFflag2[5][7] = 0;
						EFflag2[6][7] = 0;
						EFflag2[7][7] = 0;
						EFflag2[1][8] = 0;
						EFflag2[2][8] = 0;
						EFflag2[4][8] = 0;
						EFflag2[5][8] = 0;
						EFflag2[8][8] = 0;
						EFflag2[4][9] = 0;
						EFflag2[5][9] = 0;
					}
				}
			
				playerTimer = 0;
				count = 0;
				bollX = 200;
				bollY = 300;
				bollX2 = 150;
				bollY2 = 300;
				speed = 5;
				speed2 = 5;
				bollflag = 1;
				playerX = 300;
				playerY = 700;;
				playerR = 64;
				point = 49;
				point2 = 49;
				point3 = 49;
				score = 0;
				TITLETIMER = 0;
				PlaySoundMem(OPS, DX_PLAYTYPE_LOOP, TopPositionFlag = 0);
				playerflag = 0;
			}

			if (gameoverTime2 == 2 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				break;
			}

			if (count >= 500)
			{
				break;
			}
		}

		else if (scene == 5)
		{
			ChangeVolumeSoundMem(170 * 80 / 100, EDS);
			PlaySoundMem(EDS, DX_PLAYTYPE_LOOP, TopPositionFlag = 0);
			if (EDY >= -1600)
			{
				EDY = EDY - 1;
			}
		}
		//描画処理	
		if (scene == 0)
		{
			if (TITLETIMER >= 0 && TITLETIMER < 5)
			{
				DrawGraph(titleX, titleY, Title[0], TRUE);
			}

			else if (TITLETIMER >= 5 && TITLETIMER < 10)
			{
				DrawGraph(titleX, titleY, Title[1], TRUE);
			}

			else if (TITLETIMER >= 10 && TITLETIMER < 15)
			{
				DrawGraph(titleX, titleY, Title[2], TRUE);
			}

			else if (TITLETIMER >= 15 && TITLETIMER < 20)
			{
				DrawGraph(titleX, titleY, Title[3], TRUE);
			}

			else if (TITLETIMER >= 20 && TITLETIMER < 25)
			{
				DrawGraph(titleX, titleY, Title[4], TRUE);
			}

			else if (TITLETIMER >= 25 && TITLETIMER < 30)
			{
				DrawGraph(titleX, titleY, Title[5], TRUE);
			}

			else if (TITLETIMER >= 30 && TITLETIMER < 35)
			{
				DrawGraph(titleX, titleY, Title[6], TRUE);
			}

			else if (TITLETIMER >= 35 && TITLETIMER < 40)
			{
				DrawGraph(titleX, titleY, Title[7], TRUE);
			}

			else if (TITLETIMER >= 40 && TITLETIMER < 45)
			{
				DrawGraph(titleX, titleY, Title[8], TRUE);
			}

			else if (TITLETIMER >= 45 && TITLETIMER < 50)
			{
				DrawGraph(titleX, titleY, Title[9], TRUE);
			}

			else if (TITLETIMER >= 50 && TITLETIMER < 55)
			{
				DrawGraph(titleX, titleY, Title[10], TRUE);
			}

			else if (TITLETIMER >= 55 && TITLETIMER < 60)
			{
				DrawGraph(titleX, titleY, Title[11], TRUE);
			}

			else if (TITLETIMER >= 60 && TITLETIMER < 65)
			{
				DrawGraph(titleX, titleY, Title[12], TRUE);
			}

			else if (TITLETIMER >= 65 && TITLETIMER < 70)
			{
				DrawGraph(titleX, titleY, Title[13], TRUE);
			}

			else if (TITLETIMER >= 70 && TITLETIMER < 75)
			{
				DrawGraph(titleX, titleY, Title[14], TRUE);
			}

			else if (TITLETIMER >= 75 && TITLETIMER < 80)
			{
				DrawGraph(titleX, titleY, Title[15], TRUE);
			}

			else if (TITLETIMER >= 80 && TITLETIMER < 85)
			{
				DrawGraph(titleX, titleY, Title[16], TRUE);
			}

			else if (TITLETIMER >= 85 && TITLETIMER < 90)
			{
				DrawGraph(titleX, titleY, Title[17], TRUE);
			}

			else if (TITLETIMER >= 90 && TITLETIMER < 95)
			{
				DrawGraph(titleX, titleY, Title[18], TRUE);
			}

			else if (TITLETIMER >= 95 && TITLETIMER < 100)
			{
				DrawGraph(titleX, titleY, Title[19], TRUE);
			}

			else if (TITLETIMER >= 100 && TITLETIMER < 105)
			{
				DrawGraph(titleX, titleY, Title[20], TRUE);
			}

			else if (TITLETIMER >= 105 && TITLETIMER < 110)
			{
			DrawGraph(titleX, titleY, Title[21], TRUE);
			}

			else if (TITLETIMER >= 110 && TITLETIMER < 115)
			{
			DrawGraph(titleX, titleY, Title[22], TRUE);
			}

			else if (TITLETIMER >= 115 && TITLETIMER < 120)
			{
			DrawGraph(titleX, titleY, Title[23], TRUE);
			}

			else if (TITLETIMER >= 120 && TITLETIMER < 125)
			{
			DrawGraph(titleX, titleY, Title[24], TRUE);
			}

			else if (TITLETIMER >= 125 && TITLETIMER < 130)
			{
			DrawGraph(titleX, titleY, Title[25], TRUE);
			}

			else if (TITLETIMER >= 130 && TITLETIMER < 135)
			{
			DrawGraph(titleX, titleY, Title[26], TRUE);
			}

			else if (TITLETIMER >= 135 && TITLETIMER < 140)
			{
			DrawGraph(titleX, titleY, Title[27], TRUE);
			}

			else if (TITLETIMER >= 140 && TITLETIMER < 150)
			{
			DrawGraph(titleX, titleY, Title[28], TRUE);
			}

			else if (TITLETIMER >= 150 && TITLETIMER < 160)
			{
			DrawGraph(titleX, titleY, Title[29], TRUE);
			}

			else if (TITLETIMER >= 160 && TITLETIMER < 170)
			{
			DrawGraph(titleX, titleY, Title[30], TRUE);
			}

			else if (TITLETIMER >= 170 && TITLETIMER <= 180)
			{
			DrawGraph(titleX, titleY, Title[31], TRUE);
			}
		}

		else if (scene == 1)
		{
			DrawGraph(selectX, selectY, select[selectTime], TRUE);
		}


		else if (scene == 2)
		{
			DrawGraph(backX, backY, back[0], TRUE);

			if (HP == 3 || HP == 2 || HP == 1 && bollflag == 1 && fireflag == 1)
			{
				DrawGraph(bollX, bollY, Fire[fireTimer], TRUE);
			}
			else if (HP == 3 || HP == 2 || HP == 1 && bollflag == 1 && fireflag == 0)
			{
				DrawGraph(bollX, bollY, boll, TRUE);
			}

			if (deadflag == 1)
			{
				if (bolldeadTimer > 0 && bolldeadTimer <= 5)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[0], TRUE);
				}

				else if (bolldeadTimer > 5 && bolldeadTimer <= 10)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[1], TRUE);
				}

				else if (bolldeadTimer > 10 && bolldeadTimer <= 15)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[2], TRUE);
				}

				else if (bolldeadTimer > 15 && bolldeadTimer <= 20)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[3], TRUE);
				}

				else if (bolldeadTimer > 20 && bolldeadTimer <= 25)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[4], TRUE);
				}

				else if (bolldeadTimer > 25 && bolldeadTimer <= 30)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[5], TRUE);
				}

				else if (bolldeadTimer > 30 && bolldeadTimer <= 35)
				{
					DrawGraph(bolldeadX, bolldeadY, bolldead[6], TRUE);
				}

			
			}


			if (playerTimer < 5)
			{
				DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[1], TRUE);
			}

			else if (5 <= playerTimer && playerTimer < 10)
			{
				DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[2], TRUE);
			}

			else if (10 <= playerTimer && playerTimer < 150)
			{
				DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[3], TRUE);
			}

			else if (150 <= playerTimer && playerTimer < 155)
			{
				DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[4], TRUE);
			}

			else if (155 <= playerTimer && playerTimer < 250)
			{
				DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[5], TRUE);
			}

			//ブロックの表示
			for (int i = 1; i < 9; i++)
			{
				for (int j = 1; j < 6; j++)
				{
					if (blockflag[i][j] == 1)
					{
						if (j == 1)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[3], TRUE);
						}

						else if (j == 2)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[1], TRUE);
						}

						else if (j == 3)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[2], TRUE);
						}

						else if (j == 4)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[0], TRUE);
						}

						else if (j == 5)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[4], TRUE);
						}
					}

				}
			}

			//エフェクトの表示
			for (int i = 1; i < 9; i++)
			{
				for (int j = 1; j < 6; j++)
				{
					if (EFflag[i][j] == 1)
					{
						if (j == 1)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF4[EFtimer[i][j]], TRUE);
						}

						else if (j == 2)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF5[EFtimer[i][j]], TRUE);
						}

						else if (j == 3)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF3[EFtimer[i][j]], TRUE);
						}

						else if (j == 4)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF[EFtimer[i][j]], TRUE);
						}

						else if (j == 5)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF2[EFtimer[i][j]], TRUE);
						}
					}
				}
			}

			//HPの表示
			if (HP == 3)
			{
				DrawGraph(HPX, HPY, HPgh[0], TRUE);
				DrawGraph(HPX + 100, HPY, HPgh[1], TRUE);
				DrawGraph(HPX + 200, HPY, HPgh[2], TRUE);
			}

			else if (HP == 2)
			{
				DrawGraph(HPX, HPY, HPgh[0], TRUE);
				DrawGraph(HPX + 100, HPY, HPgh[1], TRUE);
			}

			else if (HP == 1)
			{
				DrawGraph(HPX, HPY, HPgh[0], TRUE);
			}

			//スコア表示
			sprintf_s(strNum, sizeof(strNum), "%d", number);
			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - 49;
				DrawGraph(i * 64 + 850, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point;
				DrawGraph(i * 64 + 770, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point2;
				DrawGraph(i * 64 + 690, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point3;
				DrawGraph(i * 64 + 610, 230, graphHandle[ghIndex], TRUE);
			}
			if (SPflag == 1 && playerflag == 0)
			{
				DrawExtendGraph(SPX - SPR, SPY - SPR2, SPX + SPR, SPY + SPR2, SP, TRUE);
			}
		}

		else if (scene == 3)
		{
			//背景
			DrawGraph(backX, backY, back[1], TRUE);
			//プレイヤー
			DrawExtendGraph(playerX - playerR, playerY - playerR2, playerX + playerR, playerY + playerR2, player[5], TRUE);
			//弾の表示
			if (HP == 3 || HP == 2 || HP == 1 && bollflag == 1 && fireflag == 1)
			{
				DrawGraph(bollX2, bollY2, Fire[fireTimer], TRUE);
			}
			else if (HP == 3 || HP == 2 || HP == 1 && bollflag == 1 && fireflag == 0)
			{
				DrawGraph(bollX2, bollY2, boll, TRUE);
			}

			//HPの表示
			if (HP2 == 1)
			{
				DrawGraph(HPX + 80, HPY, HPgh[0], TRUE);
			}

			//スコア表示
			sprintf_s(strNum, sizeof(strNum), "%d", number);
			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - 49;
				DrawGraph(i * 64 + 850, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point;
				DrawGraph(i * 64 + 770, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point2;
				DrawGraph(i * 64 + 690, 230, graphHandle[ghIndex], TRUE);
			}

			for (int i = 0; i < 1; i++)
			{
				//DrawFormatString(i * 20, 0, GetColor(255, 255, 255), "%c\n", strNum[i]);
				ghIndex = strNum[i] - point3;
				DrawGraph(i * 64 + 610, 230, graphHandle[ghIndex], TRUE);
			}
			if (SPflag == 1 && playerflag == 0)
			{
				DrawExtendGraph(SPX - SPR, SPY - SPR2, SPX + SPR, SPY + SPR2, SP, TRUE);
			}

			//ブロック表示
			for (int i = 1; i < 9; i++)
			{
				for (int j = 1; j < 10; j++)
				{

					if (blockflag2[i][j] == 1)
					{
						if (j == 5 && i == 2 || j == 5 && i == 3 || j == 5 && i == 6 || j == 5 && i == 7 || j == 6 && i == 3 || j == 6 && i == 6)
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[3], TRUE);
						}

						else
						{
							DrawExtendGraph(i * blockX - blockR + 32, j * blockY - blockR2 + 50, i * blockX + blockR + 32, j * blockY + blockR2 + 50, block[0], TRUE);
						}
					}

				}
			}
			//エフェクト
			for (int i = 1; i < 9; i++)
			{
				for (int j = 1; j < 10; j++)
				{
					if (EFflag2[i][j] == 1)
					{
						if (j == 5 && i == 2 || j == 5 && i == 3 || j == 5 && i == 6 || j == 5 && i == 7 || j == 6 && i == 3 || j == 6 && i == 6)
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF4[EFtimer2[i][j]], TRUE);
						}

						else
						{
							DrawExtendGraph(i * EFX - EFR + 32, j * EFY - EFR2 + 50, i * EFX + EFR + 32, j * EFY + EFR2 + 50, EF[EFtimer2[i][j]], TRUE);
						}
					}
				
				}
			}

		}

		else if (scene == 4)
		{
				if (count >= 0 && count < 50)
				{
					DrawGraph(gameoverX, gameoverY, gameover[0], TRUE);
				}

				else if (count >= 50 && count < 100)
				{
					DrawGraph(gameoverX, gameoverY, gameover[1], TRUE);
				}

				else if (count >= 100 && count < 150)
				{
					DrawGraph(gameoverX, gameoverY, gameover[2], TRUE);
				}

				else if (count >= 150 && count < 200)
				{
					DrawGraph(gameoverX, gameoverY, gameover[3], TRUE);
				}

				else if (count >= 200 && count < 250)
				{
					DrawGraph(gameoverX, gameoverY, gameover[4], TRUE);
				}

				else if (count >= 250 && count < 300)
				{
					DrawGraph(gameoverX, gameoverY, gameover[5], TRUE);
				}

				else if (count >= 300 && count < 350)
				{
					DrawGraph(gameoverX, gameoverY, gameover[6], TRUE);
				}

				else if (count >= 350 && count < 400)
				{
					DrawGraph(gameoverX, gameoverY, gameover[7], TRUE);
				}

				else if (count >= 400 && count < 450)
				{
					DrawGraph(gameoverX, gameoverY, gameover[8], TRUE);
				}

				else if (count >= 450 && count < 500)
				{
					DrawGraph(gameoverX, gameoverY, gameover[9], TRUE);
				}
			DrawGraph(gameover2X, gameover2Y, gameover2[gameoverTime2], TRUE);
			DrawGraph(SELECT2X, SELECT2Y, SELECT2, TRUE);
		}

		else if (scene == 5)
		{
			DrawGraph(EDX, EDY, ED, TRUE);
		}
		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}