/*
 * SettingLayer.cpp
 *
 *  Created on: 2013-7-14
 *      Author: maxing
 */

#include "Config.h"
#include "SettingLayer.h"
#include "Record.h"
#include "AudioManager.h"
#include <cocos2d.h>

using namespace cocos2d;

const char* SETTING_KEY_BGMUSIC_MUTE    = "bgMusicMute";
const char* SETTING_KEY_EFFECT_MUTE     = "effectMute";
const char* SETTING_KEY_AVATAR_ID       = "avatarId";

SettingLayer* SettingLayer::m_sharedLayer = NULL;
SettingLayer* SettingLayer::sharedLayer() {
    if (m_sharedLayer == NULL) {
        m_sharedLayer = SettingLayer::create();
        m_sharedLayer->retain();
    }

    return m_sharedLayer;
}

SettingLayer::SettingLayer() {
}

SettingLayer::~SettingLayer() {
}

bool SettingLayer::init() {
    bool bRet = false;
    do {
        CC_BREAK_IF(! CCLayer::init() );
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        this->ignoreAnchorPointForPosition(false);
        this->setAnchorPoint(CCPoint(0.5, 0.5));
        this->setPosition(CCPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        m_container = CCNode::create();
        m_container->setPosition(CCPoint(this->getContentSize().width / 2, this->getContentSize().height / 2));
        m_container->setAnchorPoint(CCPoint(0.5, 0.5));
        this->addChild(m_container);

        m_bgSprite = CCSprite::createWithSpriteFrameName("setting_bg.png");
        m_bgSprite->setPosition(CCPoint(0, 0));
        m_bgSprite->setAnchorPoint(CCPoint(0, 0));
        m_container->addChild(m_bgSprite, 0);
        m_container->setContentSize(m_bgSprite->getContentSize());

        m_musicLabel = CCLabelTTF::create("音乐", "Marker Felt.ttf", 60, CCSize(144, 80),
                kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        m_musicLabel->setColor(ccc3(31, 158, 28));
        m_musicLabel->setPosition(CCPoint(100, 440));
        m_musicLabel->setAnchorPoint(CCPoint(0.5, 0.5));
        m_container->addChild(m_musicLabel, 10);

        m_musicSelectSprite = CCSprite::createWithSpriteFrameName("select.png");
        m_musicSelectSprite->setPosition(CCPoint(300, 440));
        m_musicSelectSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_musicSelectSprite->setScale(1.5);
        m_container->addChild(m_musicSelectSprite, 100);

        m_musicSelectBgSprite = CCSprite::createWithSpriteFrameName("select_bg.png");
        m_musicSelectBgSprite->setPosition(CCPoint(300, 440));
        m_musicSelectBgSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_musicSelectBgSprite->setScale(1.5);
        m_container->addChild(m_musicSelectBgSprite, 10);

        m_linesprite1 = CCSprite::createWithSpriteFrameName("bk_line.png");
        m_linesprite1->setPosition(CCPoint(m_bgSprite->getContentSize().width / 2, 385));
        m_linesprite1->setAnchorPoint(CCPoint(0.5, 0.5));
        m_container->addChild(m_linesprite1, 0);

        m_effectLabel = CCLabelTTF::create("音效", "Marker Felt.ttf", 60, CCSize(144, 80),
                kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        m_effectLabel->setColor(ccc3(31, 158, 28));
        m_effectLabel->setPosition(CCPoint(100, 340));
        m_effectLabel->setAnchorPoint(CCPoint(0.5, 0.5));
        m_container->addChild(m_effectLabel, 10);


        m_effectSelectSprite = CCSprite::createWithSpriteFrameName("select.png");
        m_effectSelectSprite->setPosition(CCPoint(300, 340));
        m_effectSelectSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_effectSelectSprite->setScale(1.5);
        m_container->addChild(m_effectSelectSprite, 100);

        m_effectSelectBgSprite = CCSprite::createWithSpriteFrameName("select_bg.png");
        m_effectSelectBgSprite->setPosition(CCPoint(300, 340));
        m_effectSelectBgSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_effectSelectBgSprite->setScale(1.5);
        m_container->addChild(m_effectSelectBgSprite, 10);

        m_linesprite2 = CCSprite::createWithSpriteFrameName("bk_line.png");
        m_linesprite2->setPosition(CCPoint(m_bgSprite->getContentSize().width / 2, 285));
        m_linesprite2->setAnchorPoint(CCPoint(0.5, 0.5));
        m_container->addChild(m_linesprite2, 0);

        loadSettings();
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

bool SettingLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void SettingLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = m_container->convertToNodeSpace(touch->getLocation());
    CCPoint startLoc = m_container->convertToNodeSpace(touch->getStartLocation());
    if (abs(startLoc.x - location.x) >= MIN_MOVE_GAP || abs(startLoc.y - location.y) >= MIN_MOVE_GAP)
        return;

    if (m_musicSelectBgSprite->boundingBox().containsPoint(location)) {
        m_bgMusicMute = !m_bgMusicMute;
        CCLog("setBackgroundMute %d", m_bgMusicMute);
        AudioManager::instance()->setBackgroundMute(m_bgMusicMute);
        updateSettingLayer();
        saveSettings();
    }
    else if (m_effectSelectBgSprite->boundingBox().containsPoint(location)) {
        m_effectMute = !m_effectMute;
        CCLog("setSoundEffectMute %d", m_effectMute);
        AudioManager::instance()->setSoundEffectMute(m_effectMute);
        updateSettingLayer();
        saveSettings();
    }
}

void SettingLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);
}

void SettingLayer::keyBackClicked() {
    saveSettings();
    this->runHideAnimation();
}

void SettingLayer::setAvatarId(int id) {
    m_avatarId = id;
    saveSettings();
}

void SettingLayer::show() {
    if (getParent() != NULL)
        return;

    CCScene* runningScene = CCDirector::sharedDirector()->getRunningScene();
    runningScene->addChild(this, 10000);
    runShowAnimation();
}

void SettingLayer::updateSettingLayer() {
    if (m_bgMusicMute)
        m_musicSelectSprite->setVisible(false);
    else
        m_musicSelectSprite->setVisible(true);
    if (m_effectMute)
        m_effectSelectSprite->setVisible(false);
    else
        m_effectSelectSprite->setVisible(true);
}

void SettingLayer::loadSettings() {
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    m_bgMusicMute = ud->getBoolForKey(SETTING_KEY_BGMUSIC_MUTE);
    m_effectMute = ud->getBoolForKey(SETTING_KEY_EFFECT_MUTE);
    m_avatarId = ud->getIntegerForKey(SETTING_KEY_AVATAR_ID);

    AudioManager::instance()->setBackgroundMute(m_bgMusicMute);
    AudioManager::instance()->setSoundEffectMute(m_effectMute);
    CCLog("bgMute %d, effectMute %d", m_bgMusicMute, m_effectMute);
    updateSettingLayer();
}

void SettingLayer::saveSettings() {
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    ud->setBoolForKey(SETTING_KEY_BGMUSIC_MUTE, m_bgMusicMute);
    ud->setBoolForKey(SETTING_KEY_EFFECT_MUTE, m_effectMute);
    ud->setIntegerForKey(SETTING_KEY_AVATAR_ID, m_avatarId);
    //ud->flush();
}

void SettingLayer::runShowAnimation() {
    this->setScale(0.5);
    CCFiniteTimeAction* scale = CCEaseBackOut::create(CCScaleTo::create(0.3, 1));
    this->runAction(scale);
}

void SettingLayer::runHideAnimation() {
    CCFiniteTimeAction* scale = CCScaleTo::create(0.1, 0.5);
    CCFiniteTimeAction* callBack = CCCallFunc::create(this, callfunc_selector(SettingLayer::removeFromParent));
    this->runAction(CCSequence::create(scale, callBack, NULL));
}

