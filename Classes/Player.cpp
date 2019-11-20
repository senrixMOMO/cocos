#include "Player.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "OPRT_KEY.h"
#else
#include "OPRT_TOUCH.h"
#endif

#include "actionCtl.h"

USING_NS_CC;

Player::Player()
{
	anim_type = ANIM_IDLE;
	speed = 5;
	Init();
}

Player::~Player()
{
	animation[ANIM_IDLE]->release();
	animation[ANIM_RUN]->release();
	animation[ANIM_JUMP]->release();
}

Player * Player::createPlayer()
{
	return Player::create();
}

bool Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		oprt_state.reset(new OPRT_KEY(this));
	#else
		oprt_state.reset(new OPRT_TOUCH());
	#endif


	InitAnim();
	act = new actionCtl();
	//player初期位置設定
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height / 2 + origin.y));
	this->scheduleUpdate();
	//void (Player::*fpFunc)() = Player::func;
	//(this->*fpFunc)();

	return true;
}

//アニメーション初期化
void Player::InitAnim()
{
	auto Cache = cocos2d::SpriteFrameCache::getInstance();
	Cache->addSpriteFramesWithFile("plist/player-idle.plist");
	Cache->addSpriteFramesWithFile("plist/player-run.plist");
	Cache->addSpriteFramesWithFile("plist/player-jump.plist");
	auto anim = AnimationCache::getInstance();
	animation[ANIM_IDLE] = Animation::create();
	animation[ANIM_RUN] = Animation::create();
	animation[ANIM_JUMP] = Animation::create();
	//anim->addAnimation(, );
	for (auto str : idle)
	{
		animation[ANIM_IDLE]->addSpriteFrame(Cache->getSpriteFrameByName(str));
	}
	for (auto str : run)
	{
		animation[ANIM_RUN]->addSpriteFrame(Cache->getSpriteFrameByName(str));
	}
	for (auto str : jump)
	{
		animation[ANIM_JUMP]->addSpriteFrame(Cache->getSpriteFrameByName(str));
	}
	animation[ANIM_IDLE]->setDelayPerUnit(0.2f);
	animation[ANIM_RUN]->setDelayPerUnit(0.09f);
	animation[ANIM_JUMP]->setDelayPerUnit(0.09f);

	animation[ANIM_IDLE]->setRestoreOriginalFrame(true);
	animation[ANIM_RUN]->setRestoreOriginalFrame(true);
	animation[ANIM_JUMP]->setRestoreOriginalFrame(true);

	auto repeatAnimIdle = RepeatForever::create(Animate::create(animation[ANIM_IDLE]));

	//for (auto &a : animation)
	//{
	//	a->retain();
	//}
	animation[ANIM_IDLE]->retain();
	animation[ANIM_RUN]->retain();
	animation[ANIM_JUMP]->retain();

	auto flip = FlipX::create(false);
	auto flip2 = FlipY::create(false);

	//初期アニメーション設定
	this->runAction(repeatAnimIdle);

	this->runAction(flip);
	this->runAction(flip2);
}

void Player::InitAnim(std::string str)
{
	auto Cache = cocos2d::SpriteFrameCache::getInstance();

	Cache->addSpriteFramesWithFile("plist/player-" + str + ".plist");

	if (str == "idle")
	{
		animation[ANIM_IDLE] = Animation::create();
		for (auto str : idle)
		{
			animation[ANIM_IDLE]->addSpriteFrame(Cache->getSpriteFrameByName(str));
		}
	}
}

//update
void Player::update(float delta)
{
	oprt_state->Update(this);
	if(ActName == "右移動")
	{
		CheckHitTileLR(speed, "右移動");
		if (oprt_state->keyFlag)
		{
			act->MoveLR(speed, this);
		}
	}
	if (ActName == "左移動")
	{
		CheckHitTileLR(speed, "左移動");
		if (oprt_state->keyFlag)
		{
			act->MoveLR(-speed, this);
		}
	}
	if (ActName == "ジャンプ")
	{
		if (oprt_state->keyFlag)
		{
			act->Jump(this);
		}
	}
	if (ActName == "何もしない")
	{
		anim_type = ANIM_IDLE;
	}
	PlayerMove();
	CheckHitTile(2);
	ChangeAnim();
}

//タイルとの当たり判定 //move 速度
void Player::CheckHitTile(int move)
{
	//playerのサイズ
	auto height_size = 120;
	auto width_size = 60;

	auto tileSize = 48;

	////RECT
	//auto rect1 = Vec2(this->getPosition());															//左上
	//auto rect2 = Vec2(this->getPositionX() + width_size, this->getPositionY());						//右上
	//auto rect3 = Vec2(this->getPositionX(), this->getPositionY() + height_size);					//左下		
	//auto rect4 = Vec2(this->getPositionX() + width_size, this->getPositionY() + height_size);		//右下

	auto director = Director::getInstance();
	auto diremap = (TMXTiledMap*)director->getRunningScene()->getChildByName("map");

	//レイヤー取得
	auto collision = diremap->getLayer("collision");
	auto layerSize = collision->getLayerSize();

	//下判定
	auto px_down = this->getPositionX() / tileSize;
	auto py_down = layerSize.height - (this->getPositionY() - width_size) / tileSize;

	if (px_down < layerSize.width && py_down < layerSize.height && px_down >= 0 && py_down >= 0)
	{
		if ((collision->getTileGIDAt(Vec2(px_down, py_down)) != 0 && oprt_state->keyFlag))
		{
			this->setPositionY(this->getPositionY() + move);
		}
	}

	if (collision->getTileGIDAt(Vec2(px_down, py_down)) == 0)
	{
		this->setPositionY(this->getPositionY() - move);
	}

	//上判定
	auto px_up = this->getPositionX() / tileSize;
	auto py_up = layerSize.height - (this->getPositionY()) / tileSize;

	if (px_up < layerSize.width && py_up < layerSize.height && px_up >= 0 && py_up >= 0)
	{
		if (collision->getTileGIDAt(Vec2(px_up, py_up)) != 0 && oprt_state->keyFlag)
		{
			oprt_state->keyFlag = false;
			this->setPositionY(this->getPositionY() - move);
		}
	}

}

void Player::CheckHitTileLR(int move, std::string actName)
{
	//playerのサイズ
	auto height_size = 120;
	auto width_size = 60;

	auto tileSize = 48;

	////RECT
	//auto rect1 = Vec2(this->getPosition());															//左上
	//auto rect2 = Vec2(this->getPositionX() + width_size, this->getPositionY());						//右上
	//auto rect3 = Vec2(this->getPositionX(), this->getPositionY() + height_size);					//左下		
	//auto rect4 = Vec2(this->getPositionX() + width_size, this->getPositionY() + height_size);		//右下

	auto director = Director::getInstance();
	auto diremap = (TMXTiledMap*)director->getRunningScene()->getChildByName("map");

	//レイヤー取得
	auto collision = diremap->getLayer("collision");
	auto layerSize = collision->getLayerSize();

	if (actName == "右移動")
	{
		//右判定
		auto px_right = (this->getPositionX() + width_size / 2) / tileSize;
		auto py_right = layerSize.height - this->getPositionY() / tileSize;

		if (px_right < layerSize.width && py_right < layerSize.height && px_right >= 0 && py_right >= 0)
		{
			if (collision->getTileGIDAt(Vec2(px_right, py_right)) != 0 && oprt_state->keyFlag)
			{
				oprt_state->keyFlag = false;
				this->setPositionX(this->getPositionX() - move);
			}
		}
	}
	if (actName == "左移動")
	{
		//左判定
		auto px_left = (this->getPositionX() - width_size / 2) / tileSize;
		auto py_left = layerSize.height - this->getPositionY() / tileSize;

		if (px_left < layerSize.width && py_left < layerSize.height && px_left >= 0 && py_left >= 0)
		{
			if (collision->getTileGIDAt(Vec2(px_left, py_left)) != 0 && oprt_state->keyFlag)
			{
				oprt_state->keyFlag = false;
				this->setPositionX(this->getPositionX() + move);
			}
		}
	}
}

//アニメーション切り替え
void Player::ChangeAnim()
{
	if (oprt_state->input_key == Input::RIGHT)
	{
		if (anim_type != ANIM_RUN)
		{
			this->stopAllActions();
			auto flip = FlipX::create(false);
			auto repeatAnimRun = RepeatForever::create(Animate::create(animation[ANIM_RUN]));
			this->runAction(repeatAnimRun);
			this->runAction(flip);
		}
		anim_type = ANIM_RUN;
	}
	else if (oprt_state->input_key == Input::LEFT)
	{
		if (anim_type != ANIM_RUN)
		{
			this->stopAllActions();
			auto flip = FlipX::create(true);
			auto repeatAnimRun = RepeatForever::create(Animate::create(animation[ANIM_RUN]));
			this->runAction(repeatAnimRun);
			this->runAction(flip);
		}
		anim_type = ANIM_RUN;
	}
	else if (oprt_state->input_key == Input::Z)
	{
		if (anim_type != ANIM_JUMP)
		{
			this->stopAllActions();
			//auto flip = FlipX::create(true);
			auto AnimJump = Animate::create(animation[ANIM_JUMP]);
			this->runAction(AnimJump);
			//this->runAction(flip);
		}
		anim_type = ANIM_JUMP;
	}
	else
	{
		if (anim_type != ANIM_JUMP)
		{
			if (anim_type != ANIM_IDLE)
			{
				this->stopAllActions();
				auto repeatAnimIdle = RepeatForever::create(Animate::create(animation[ANIM_IDLE]));
				this->runAction(repeatAnimIdle);
			}
			anim_type = ANIM_IDLE;
		}
	}
}

void Player::PlayerMove()
{
	switch (oprt_state->input_key)
	{
	case Input::LEFT:
		ActName = "左移動";
		break;
	case Input::RIGHT:
		ActName = "右移動";
		break;
	case Input::Z:
		ActName = "ジャンプ";
		break;
	case Input::DOWN:
		ActName = "落ちる";
		break;
	case Input::NON:
		ActName = "何もしない";
		break;
	default:
		break;
	}
}

//ANIM Player::GetAnimType()
//{
//	return anim_type;
//}