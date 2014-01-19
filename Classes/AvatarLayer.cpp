/*
 * AvatarLayer.cpp
 *
 *  Created on: 2013-7-14
 *      Author: maxing
 */

#include "Config.h"
#include "AvatarLayer.h"
#include "SettingLayer.h"

using namespace cocos2d;

AvatarLayer::AvatarLayer() {
}

AvatarLayer::~AvatarLayer() {
}

bool AvatarLayer::init() {
    bool bRet = false;
    do {
        CC_BREAK_IF(! CCLayer::init() );

        m_avatarFrame = CCSprite::createWithSpriteFrameName("touxiangkuang.png");
        m_avatarFrame->setPosition(CCPoint(0, 0));
        m_avatarFrame->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_avatarFrame);
        this->setContentSize(m_avatarFrame->getContentSize());

        CCString* s;
        m_avatarCenter = CCPoint(52.5, 107.5);
        for (int i = 0; i < MAX_AVATAR_COUNT; i++) {
            s = CCString::createWithFormat("touxiang%d.png", i+1);
            m_avatarList[i] = CCSprite::createWithSpriteFrameName(s->getCString());
            m_avatarList[i]->setAnchorPoint(CCPoint(0.5, 0.5));
            m_avatarList[i]->setPosition(m_avatarCenter);
            m_avatarList[i]->setVisible(false);
            this->addChild(m_avatarList[i]);
        }

        m_showId = SettingLayer::sharedLayer()->avatarId();
        m_isShowAll = false;
        m_avatarList[m_showId]->setVisible(true);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

bool AvatarLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    return true;
}

void AvatarLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = convertToNodeSpace(touch->getLocation());
    CCPoint startLoc = convertToNodeSpace(touch->getStartLocation());

    //CCLog("touch in AvatarLayer, location %0.2f, %0.2f, showAll %d", location.x, location.y, m_isShowAll);
    if (!m_isShowAll) {
        if (abs(startLoc.x - location.x) >= MIN_MOVE_GAP || abs(startLoc.y - location.y) >= MIN_MOVE_GAP)
            return;
        //CCRect r = m_avatarList[m_showId]->boundingBox();
        //CCLog("showId %d, boundingBox: %0.2f, %0.2f, %0.2f, %0.2f", m_showId, r.origin.x, r.origin.y, r.size.width, r.size.height);
        if (m_avatarList[m_showId]->boundingBox().containsPoint(location)) {
            unpackAvatar();
        }
    }
    else {
        for (int i = 0; i < MAX_AVATAR_COUNT; i++) {
            if (m_avatarList[i]->boundingBox().containsPoint(location)) {
                m_showId = i;
                SettingLayer::sharedLayer()->setAvatarId(m_showId);
                break;
            }
        }
        packAvatar();
    }
}

void AvatarLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -100, false);
}

void AvatarLayer::unpackAvatar() {
    m_isShowAll = true;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    for (int i = 0; i < MAX_AVATAR_COUNT; i++) {
        CCFiniteTimeAction* scale = CCScaleTo::create(0.2, 1.5);
        CCFiniteTimeAction* move = CCMoveTo::create(0.2,
                convertToNodeSpace(CCPoint(65 + 127.5 * i, visibleSize.height/2)));
        m_avatarList[i]->setVisible(true);
        m_avatarList[i]->runAction(CCSpawn::create(scale, move, NULL));
    }
}

void AvatarLayer::packAvatar() {
    m_isShowAll = false;
    CCFiniteTimeAction* callback = CCCallFunc::create(this, callfunc_selector(AvatarLayer::showSelectAvatar));
    CCFiniteTimeAction* scale = CCScaleTo::create(0.2, 1);
    CCFiniteTimeAction* move = CCMoveTo::create(0.2, m_avatarCenter);
    m_avatarList[0]->runAction(CCSequence::create(CCSpawn::create(scale, move, NULL), callback, NULL));
    for (int i = 1; i < MAX_AVATAR_COUNT; i++) {
        m_avatarList[i]->runAction(CCSpawn::create((CCFiniteTimeAction*)scale->copy(), move->copy(), NULL));
    }
}

void AvatarLayer::showSelectAvatar() {
    for (int i = 0; i < MAX_AVATAR_COUNT; i++)
        m_avatarList[i]->setVisible(false);

    if (m_showId >= 0 && m_showId < MAX_AVATAR_COUNT)
        m_avatarList[m_showId]->setVisible(true);
}
