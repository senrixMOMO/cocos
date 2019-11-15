#pragma once
#include "cocos2d.h"
#include <vector>
#include <list>

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

struct Module {
	ANIM animID;

};

//std::function<�^(����)>)

class Player : public cocos2d::Sprite
{
public:
	Player();
	~Player();
	static Player* createPlayer();

	void update(float delta);
	void CheckHitTile(int move);						//�^�C���Ƃ̓����蔻��
	void ChangeAnim();									//�A�j���[�V�����؂�ւ�

	void PlayerMove();
	ANIM GetAnimType();
private:
	CREATE_FUNC(Player);
	bool Init();
	void InitAnim();
	void SetAnim();
	cocos2d::AnimationCache* anim;
	cocos2d::Animation* animation[ANIM_MAX];			//�A�j���[�V�����z��

	//EventKeyboard::KeyCode *keyCode;

	ANIM anim_type;										//�A�j���[�V�����^�C�v
	OPRT_STATE *oprt_state;

	std::vector<std::string> idle = { "player-idle-1.png" ,"player-idle-2.png" ,"player-idle-3.png" ,"player-idle-4.png" };
	std::vector<std::string> run = { "player-run-1.png","player-run-2.png","player-run-3.png","player-run-4.png","player-run-5.png","player-run-6.png","player-run-7.png","player-run-8.png","player-run-9.png","player-run-10.png" };
	std::vector<std::string> jump = { "player-jump-1.png","player-jump-2.png","player-jump-3.png","player-jump-4.png","player-jump-5.png","player-jump-6.png"};
};

//module��
//��̊֐��ɕ����̋@�\���������Ȃ�
//�����_���A�֐��|�C���^�A�֐��I�u�W�F�N�g�A�N���X���Ȃǂ�

//playrt

//actionCtl
//actionlist ���ړ� etc

//�֐��I�u�W�F�N�g
//�L�[���̓`�F�b�N(keyCode)
//hitcheck
//status
//�L�����ړ�(�x�N�g��)