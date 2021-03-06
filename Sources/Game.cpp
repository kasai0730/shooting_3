#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)-
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)-


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
bool    flag = false;


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);        // 砲台の位置変更(HW16A115 田中雄登)
    targetRect = Rect(280, -140, 40, 40);   // ターゲットの位置変更(HW16A115 田中雄登)
    bulletPos.x = -999;
    score = 0;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_explosion03.mp3");   //発射SEの追加(HW16A046 笠井智也)
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 1;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            
            PlaySound("se_maoudamashii_explosion06.mp3");   //被弾SEの追加(HW16A046 笠井智也)
        }
    }
    
    //大砲の移動を追加 (HW16A114 田中 陽大)
    if (cannonPos.y <= -150) flag = false;
    if (cannonPos.y >= -70) flag = true;
    if (flag == true) {
        cannonPos.y -= 3;
    }else{
        cannonPos.y += 3;
    }
    
    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);
    

    // 雲の描画
    if (cloudPos.x < 280) {                 // 雲が移動し、折り返して表示されるように変更(HW16A115 田中雄登)
        cloudPos.x += 70 * Time::deltaTime;
        DrawImage("cloud1.png", cloudPos);
    }
    else cloudPos.x = -320;

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 50.0f);    //スコアのサイズを大きくする(HW16A046 笠井智也)
    DrawText(FormatString("%02d", score), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%02d", score), Vector2(-320, 200), Color::white);
}

