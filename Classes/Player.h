#pragma once
#include "cocos2d.h"
#include <vector>
#include <memory>
#include "Effekseer/Effekseer.h"
#include "Cricket/ck/ck.h"
#include "Cricket/ck/config.h"
#include "Cricket/ck/bank.h"
#include "Cricket/ck/sound.h"

enum ANIM
{
	ANIM_IDLE,
	ANIM_RUN,
	ANIM_JUMP,
	ANIM_CLING,
	ANIM_DUCK,
	ANIM_HURT,
	ANIM_RUN_SHOT,
	ANIM_SHOOT_UP,
	ANIM_STAND,
	ANIM_MAX
};

class OPRT_STATE;
class actionCtl;

//std::function<型(引数)>)

class Player : public cocos2d::Sprite
{
public:
	Player();
	~Player();
	static Player* createPlayer();

	void update(float delta);

	void CheckHitTile(int move);							//タイルとの当たり判定
	void CheckHitTileLR(int move, std::string actName);		//タイルとの当たり判定
	void ChangeAnim();										//アニメーション切り替え

	void PlayerMove();

	efk::EffectManager* manager;

	int count;
	CkBank* _bank;
	CkSound* _soundEffect;
	CkSound* _music;

private:
	CREATE_FUNC(Player);
	bool Init();
	void InitAnim();
	void InitAnim(std::string str);
	void SetAnim();
	cocos2d::Animation* animation[ANIM_MAX];			//アニメーション配列

	std::string ActName;

	ANIM anim_type;										//アニメーションタイプ
	std::unique_ptr<actionCtl> act;
	std::unique_ptr<OPRT_STATE> oprt_state;
	int speed;

	std::vector<std::string> idle = { "player-idle-1.png" ,"player-idle-2.png" ,"player-idle-3.png" ,"player-idle-4.png" };
	std::vector<std::string> run = { "player-run-1.png","player-run-2.png","player-run-3.png","player-run-4.png","player-run-5.png","player-run-6.png","player-run-7.png","player-run-8.png","player-run-9.png","player-run-10.png" };
	std::vector<std::string> jump = { "player-jump-1.png","player-jump-2.png","player-jump-3.png","player-jump-4.png","player-jump-5.png","player-jump-6.png"};
};