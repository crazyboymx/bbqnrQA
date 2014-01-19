/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.cpp
 * $Id: GameLayer.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 18:40:24 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "GameLayer.h"
#include "MapLayer.h"
#include "AudioManager.h"
#include <cstdlib>
#include <algorithm>

#define ABOVE_TITLE_DIST    500

using namespace cocos2d;

GameLayer* GameLayer::m_sharedLayer = NULL;

GameLayer* GameLayer::sharedLayer() {
    if (m_sharedLayer == NULL) {
        m_sharedLayer = GameLayer::create();
        m_sharedLayer->retain();
    }

    return m_sharedLayer;
}

GameLayer::GameLayer()
    : m_level(NULL)
    , m_levelPassed(false)
{
}

GameLayer::~GameLayer() {
}

bool GameLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCSize optionContentSize(OPTIONLAYER_CONTENT_WIDTH, OPTIONLAYER_CONTENT_HEIGHT);
        //CCLog("origin %0.2f, %0.2f, visibleSize %0.2f, %0.2f", origin.x, origin.y, visibleSize.width, visibleSize.height);

        m_layerBGSprite = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("game_bg.png"));
        m_layerBGSprite->setAnchorPoint(CCPoint(0.0, 0.0));
        m_layerBGSprite->setPosition(CCPoint(origin.x, origin.y));
        this->addChild(m_layerBGSprite, 0);

        m_questionLayerPosition = CCPoint(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height - QUESTIONLAYER_CONTENT_HEIGHT));
        m_questionLayer = QuestionLayer::create();
        m_questionLayer->ignoreAnchorPointForPosition(false);
        m_questionLayer->setPosition(m_questionLayerPosition + CCPoint(0, ABOVE_TITLE_DIST));
        m_questionLayer->setAnchorPoint(CCPoint(0.5, 0.0));
        this->addChild(m_questionLayer, 100);

        m_optionAPosition = CCPoint(origin.x + visibleSize.width/2, origin.y + (optionContentSize.height + OPTIONLAYER_SPACING) * 3 + 80);
        m_option_a = OptionLayer::create();
        m_option_a->ignoreAnchorPointForPosition(false);
        m_option_a->setPosition(m_questionLayerPosition + CCPoint(0, ABOVE_TITLE_DIST));
        m_option_a->setAnchorPoint(CCPoint(0.5f, 0.0f));
        m_option_a->addObserver(this);
        this->addChild(m_option_a, 99);

        m_optionBPosition = CCPoint(origin.x + visibleSize.width/2, origin.y + (optionContentSize.height + OPTIONLAYER_SPACING) * 2 + 80);
        m_option_b = OptionLayer::create();
        m_option_b->ignoreAnchorPointForPosition(false);
        m_option_b->setPosition(m_questionLayerPosition + CCPoint(0, ABOVE_TITLE_DIST));
        m_option_b->setAnchorPoint(CCPoint(0.5f, 0.0f));
        m_option_b->addObserver(this);
        this->addChild(m_option_b, 98);

        m_optionCPosition = CCPoint(origin.x + visibleSize.width/2, origin.y + (optionContentSize.height + OPTIONLAYER_SPACING) * 1 + 80);
        m_option_c = OptionLayer::create();
        m_option_c->ignoreAnchorPointForPosition(false);
        m_option_c->setPosition(m_questionLayerPosition + CCPoint(0, ABOVE_TITLE_DIST));
        m_option_c->setAnchorPoint(CCPoint(0.5f, 0.0f));
        m_option_c->addObserver(this);
        this->addChild(m_option_c, 97);

        m_optionDPosition = CCPoint(origin.x + visibleSize.width / 2, origin.y + (optionContentSize.height + OPTIONLAYER_SPACING) * 0 + 80);
        m_option_d = OptionLayer::create();
        m_option_d->ignoreAnchorPointForPosition(false);
        m_option_d->setPosition(m_questionLayerPosition + CCPoint(0, ABOVE_TITLE_DIST));
        m_option_d->setAnchorPoint(CCPoint(0.5f, 0.0f));
        m_option_d->addObserver(this);
        this->addChild(m_option_d, 96);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::initWithLevel(Level* lvl) {
    m_level = lvl;
    m_questionLayer->initStar();
}

void GameLayer::startLevel() {
    if (m_level == NULL)
        return;

    m_level->shuffleQuestion();
    m_level->resetProgress();
    nextQuestion();
}

void GameLayer::nextQuestion() {
    m_question = m_level->nextQuestion();
    if (m_question.valid) {
        CCFiniteTimeAction *endCallBack = CCCallFunc::create(this,
                callfunc_selector(GameLayer::questionEndAnimation));
        CCFiniteTimeAction* delayAction = CCDelayTime::create(1.2f);
        CCFiniteTimeAction *updateCallBack = CCCallFunc::create(this,
                callfunc_selector(GameLayer::updateQuestionUI));
        CCFiniteTimeAction *startCallBack = CCCallFunc::create(this,
                callfunc_selector(GameLayer::questionStartAnimation));
        if (m_question.id > 1) {
            this->runAction(CCSpawn::create(endCallBack,
                        CCSequence::create(delayAction, updateCallBack, startCallBack, NULL), NULL));
        }
        else {
            this->runAction(CCSequence::create(updateCallBack, startCallBack, NULL));
        }
    }
    else
        levelComplete();
}

void GameLayer::onOptionSelected(OptionLayer* option) {
    if (m_level->fail())
        return;

    option->showAnswerAnimation();
    if (option->isAnswer())
        answerCorrect();
    else
        answerWrong();
}

void GameLayer::updateQuestionUI() {
    m_questionLayer->setQuestionTitle(m_question.question);
    int opt[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        int s = rand() % 4;
        int tmp = opt[i];
        opt[i] = opt[s];
        opt[s] = tmp;
    }

    string optStr;
    optStr = "A. "+m_question.option[opt[0]];
    m_option_a->setOption(optStr, opt[0] == m_question.option.answer);
    optStr = "B. "+m_question.option[opt[1]];
    m_option_b->setOption(optStr, opt[1] == m_question.option.answer);
    optStr = "C. "+m_question.option[opt[2]];
    m_option_c->setOption(optStr, opt[2] == m_question.option.answer);
    optStr = "D. "+m_question.option[opt[3]];
    m_option_d->setOption(optStr, opt[3] == m_question.option.answer);
}

void GameLayer::answerCorrect() {
    m_level->passCurrentQuestion();
    m_questionLayer->updateStar(m_level->starCount());
    if (m_levelPassed == false && m_level->pass()) {
        m_levelPassed = true;
        levelPass();
    }
    CCFiniteTimeAction* delayAction = CCDelayTime::create(0.8f);
    CCFiniteTimeAction *callBack = CCCallFunc::create(this, callfunc_selector(GameLayer::nextQuestion));
    this->runAction(CCSequence::create(delayAction, callBack, NULL));
}

void GameLayer::answerWrong() {
    m_level->failCurrentQuestion();
    CCFiniteTimeAction* delayAction = CCDelayTime::create(0.8f);
    CCFiniteTimeAction *callBack;
    if (m_level->fail())
        callBack = CCCallFunc::create(this, callfunc_selector(GameLayer::levelFail));
    else
        callBack = CCCallFunc::create(this, callfunc_selector(GameLayer::nextQuestion));
    this->runAction(CCSequence::create(delayAction, callBack, NULL));
}

void GameLayer::levelComplete() {
    MapLayer* layer = MapLayer::sharedLayer();
    CCScene* pScene = CCScene::create();
    pScene->addChild(layer);
    CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
}

void GameLayer::levelPass() {
}

void GameLayer::levelFail() {
    levelComplete();
}

//--------------------Animations-----------------------
void GameLayer::questionEndAnimation() {
    float t = 0.7f;
    CCFiniteTimeAction* action = CCEaseBackIn::create(CCMoveTo::create(t, m_questionLayerPosition+CCPoint(0, ABOVE_TITLE_DIST)));
    m_questionLayer->runAction(action);

    action = CCEaseBackIn::create(CCMoveTo::create(t, m_questionLayerPosition+CCPoint(0, ABOVE_TITLE_DIST)));
    m_option_a->runAction(action);
    action = CCEaseBackIn::create(CCMoveTo::create(t, m_questionLayerPosition+CCPoint(0, ABOVE_TITLE_DIST)));
    m_option_b->runAction(action);
    action = CCEaseBackIn::create(CCMoveTo::create(t, m_questionLayerPosition+CCPoint(0, ABOVE_TITLE_DIST)));
    m_option_c->runAction(action);
    action = CCEaseBackIn::create(CCMoveTo::create(t, m_questionLayerPosition+CCPoint(0, ABOVE_TITLE_DIST)));
    m_option_d->runAction(action);
    AudioManager::instance()->playEffect("chainUp.mp3");
}

void GameLayer::questionStartAnimation() {
    float t = 0.7f;
    CCFiniteTimeAction* action = CCEaseBackOut::create(CCMoveTo::create(t, m_questionLayerPosition));
    m_questionLayer->runAction(action);

    action = CCEaseBackOut::create(CCMoveTo::create(t, m_optionAPosition));
    m_option_a->runAction(action);
    action = CCEaseBackOut::create(CCMoveTo::create(t, m_optionBPosition));
    m_option_b->runAction(action);
    action = CCEaseBackOut::create(CCMoveTo::create(t, m_optionCPosition));
    m_option_c->runAction(action);
    action = CCEaseBackOut::create(CCMoveTo::create(t, m_optionDPosition));
    m_option_d->runAction(action);
    AudioManager::instance()->playEffect("chainDown.mp3");
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    //CCLog("touch in GameLayer");
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}
