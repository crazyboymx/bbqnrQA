/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: OptionLayer.cpp
 * $Id: OptionLayer.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:45 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "OptionLayer.h"
#include "AudioManager.h"
#include <algorithm>

OptionLayer::OptionLayer() {
    m_option = "";
    m_isAnswer = false;
    m_observers;
}

OptionLayer::~OptionLayer() {
}

bool OptionLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        CCSize contentSize(OPTIONLAYER_CONTENT_WIDTH, OPTIONLAYER_CONTENT_HEIGHT);
        this->setContentSize(contentSize);

        m_optionLabel = CCLabelTTF::create("", "Marker Felt.ttf", OPTION_TEXT_SIZE,
            CCSize(520, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        m_optionLabel->setAnchorPoint(CCPoint(0.0, 0.0));
        m_optionLabel->setPosition(CCPoint(30.0, 45.0));
        m_optionLabel->setColor(ccc3(26, 85, 84));
        this->addChild(m_optionLabel, 100);

        m_bgSprite = CCSprite::createWithSpriteFrameName("option_bg.png");
        m_bgSprite->setAnchorPoint(CCPoint(0.0, 0.0));
        m_bgSprite->setPosition(CCPoint(0.0, 0.0));
        this->addChild(m_bgSprite, 10);

        m_correctSprite = CCSprite::createWithSpriteFrameName("correct.png");
        m_correctSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_correctSprite->setPosition(CCPoint(60, 60));
        m_correctSprite->setScale(1.5);
        this->addChild(m_correctSprite, 1000);

        m_wrongSprite = CCSprite::createWithSpriteFrameName("wrong.png");
        m_wrongSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_wrongSprite->setPosition(CCPoint(60, 60));
        m_wrongSprite->setScale(1.5);
        this->addChild(m_wrongSprite, 1000);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void OptionLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();
    if (!this->boundingBox().containsPoint(location))
        return;

    vector<OptionObserver*>::iterator pos = m_observers.begin();
    for (;pos != m_observers.end(); ++pos) {
        (*pos)->onOptionSelected(this);
    }
}

void OptionLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void OptionLayer::addObserver(OptionObserver* observer) {
    m_observers.push_back(observer);
}

void OptionLayer::removeObserver(OptionObserver* observer) {
    m_observers.erase(remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void OptionLayer::setOption(string option, bool isAnswer) {
    m_option = option;
    string s = m_option;
    if (isAnswer)
        s += "(A)";
    m_isAnswer = isAnswer;
    m_optionLabel->setString(s.c_str());
    m_correctSprite->setVisible(false);
    m_wrongSprite->setVisible(false);
}

void OptionLayer::showAnswerAnimation() {
    if (m_isAnswer) {
        m_correctSprite->setVisible(true);
        m_wrongSprite->setVisible(false);
        AudioManager::instance()->playEffect("correct.mp3");
    }
    else {
        m_correctSprite->setVisible(false);
        m_wrongSprite->setVisible(true);
        AudioManager::instance()->playEffect("wrong.mp3");
    }
}

