/*
 * MenuLayer.cpp
 *
 *  Created on: 2013-7-14
 *      Author: maxing
 */

#include "Config.h"
#include "MenuLayer.h"
#include "MapLayer.h"
#include "AudioManager.h"

using namespace cocos2d;

MenuLayer::MenuLayer() {
}

MenuLayer::~MenuLayer() {
}

bool MenuLayer::init() {
    bool bRet = false;
    do {
        CC_BREAK_IF(! CCLayer::init() );
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        m_bgSprite = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("main_bg.png"));
        m_bgSprite->setPosition(CCPoint(0, 0));
        m_bgSprite->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_bgSprite);

        m_daSprite = CCSprite::createWithSpriteFrameName("da.png");
        m_daSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_daSprite->setPosition(CCPoint(130, 500));
        m_daSprite->setRotation(15);
        m_daSprite->setVisible(false);
        this->addChild(m_daSprite);

        m_renSprite = CCSprite::createWithSpriteFrameName("ren.png");
        m_renSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_renSprite->setPosition(CCPoint(visibleSize.width / 2, 450));
        m_renSprite->setVisible(false);
        this->addChild(m_renSprite);

        m_xiuSprite = CCSprite::createWithSpriteFrameName("xiu.png");
        m_xiuSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_xiuSprite->setPosition(CCPoint(510, 500));
        m_xiuSprite->setVisible(false);
        m_xiuSprite->setRotation(-15);
        this->addChild(m_xiuSprite);

        m_startSprite = CCSprite::createWithSpriteFrameName("start.png");
        m_startSprite->setAnchorPoint(CCPoint(0.5, 0.5));
        m_startSprite->setPosition(CCPoint(visibleSize.width / 2, 117));
        this->addChild(m_startSprite);

        this->scheduleOnce(schedule_selector(MenuLayer::darenxiuAppear), 0.5);
        this->schedule(schedule_selector(MenuLayer::darenxiuAnimation), 3, kCCRepeatForever, 3);
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void MenuLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent) {
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocation();

    if (m_startSprite->boundingBox().containsPoint(location)) {
        m_startSprite->setScale(0.9);
    }
}

void MenuLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent) {
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocation();

    if (m_startSprite->boundingBox().containsPoint(location) == false) {
        m_startSprite->setScale(1.0);
    }
}

void MenuLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent) {
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocation();
    CCPoint startLoc = touch->getStartLocation();

    m_startSprite->setScale(1.0);
    if (m_startSprite->boundingBox().containsPoint(location) &&
            m_startSprite->boundingBox().containsPoint(startLoc)) {
        AudioManager::instance()->playEffect("clickButton.ogg");
        onStartClicked();
    }
}

void MenuLayer::onStartClicked() {
    CCScene* pScene = CCScene::create();
    MapLayer* layer = MapLayer::create();
    pScene->addChild(layer);
    CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
}

void MenuLayer::darenxiuAppear() {
    CCFiniteTimeAction* delay1 = CCDelayTime::create(0.1);
    CCFiniteTimeAction* delay2 = CCDelayTime::create(0.3);
    CCFiniteTimeAction* delay3 = CCDelayTime::create(0.6);
    CCFiniteTimeAction* scale = CCScaleTo::create(0.1, 1.5);
    CCFiniteTimeAction* scale2 = CCScaleBy::create(0.1, 0.9);
    CCFiniteTimeAction* sound = CCCallFunc::create(this, callfunc_selector(MenuLayer::darenxiuSound));
    CCFiniteTimeAction* daAppear = CCCallFunc::create(this, callfunc_selector(MenuLayer::showDa));
    CCFiniteTimeAction* renAppear = CCCallFunc::create(this, callfunc_selector(MenuLayer::showRen));
    CCFiniteTimeAction* xiuAppear = CCCallFunc::create(this, callfunc_selector(MenuLayer::showXiu));

    m_daSprite->setScale(3.0);
    m_daSprite->runAction(CCSequence::create(daAppear, scale, sound, NULL));

    m_renSprite->setScale(3.0);
    m_renSprite->runAction(CCSequence::create(delay2, renAppear, scale->copy(), sound, NULL));

    m_xiuSprite->setScale(3.0);
    m_xiuSprite->runAction(CCSequence::create(delay3, xiuAppear, scale->copy(), sound, NULL));

    this->runAction(CCSequence::create(delay1, scale2, scale2->reverse(),
                                       delay1->copy(), scale2->copy(), scale2->reverse(),
                                       delay1->copy(), scale2->copy(), scale2->reverse(), NULL));
}

void MenuLayer::darenxiuAnimation() {
    CCFiniteTimeAction* delay = CCDelayTime::create(0.1);
    CCFiniteTimeAction* scale = CCScaleBy::create(0.1, 1.2);

    m_daSprite->runAction(CCSequence::create(scale, scale->reverse(), NULL));
    m_renSprite->runAction(CCSequence::create(delay, scale->copy(), scale->reverse(), NULL));
    m_xiuSprite->runAction(CCSequence::create((CCFiniteTimeAction*)delay->copy(), delay->copy(), scale->copy(), scale->reverse(), NULL));
}

void MenuLayer::darenxiuSound() {
    AudioManager::instance()->playEffect("sealPress.mp3");
}

void MenuLayer::showDa() {
    m_daSprite->setVisible(true);
}

void MenuLayer::showRen() {
    m_renSprite->setVisible(true);
}

void MenuLayer::showXiu() {
    m_xiuSprite->setVisible(true);
}
