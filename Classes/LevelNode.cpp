/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LevelNode.cpp
 * $Id: LevelNode.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:45 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "LevelNode.h"
#include <algorithm>

LevelNode::LevelNode() {
    m_level = NULL;
}

LevelNode::~LevelNode() {
}

bool LevelNode::init() {
    bool bRet = false;
    do {
        CCNode::init();

        CCSize contentSize(LEVELNODE_WIDTH, LEVELNODE_HEIGHT);
        this->setContentSize(contentSize);

        m_label = CCLabelTTF::create("", "Marker Felt.ttf", 32,
                contentSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
        m_label->setAnchorPoint(CCPoint(0.5, 0.5));
        m_label->setPosition(CCPoint(contentSize.width/2, contentSize.height/2));
        m_label->enableStroke(ccc3(0, 0, 255), 4);
        this->addChild(m_label, 10);

        m_seasonTitle = CCLabelTTF::create("", "Marker Felt.ttf", 32,
                CCSize(150, 70), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
        m_seasonTitle->setAnchorPoint(CCPoint(0.5, 0.5));
        m_seasonTitle->setPosition(CCPoint(contentSize.width/2, -30));
        m_seasonTitle->setColor(ccc3(0, 0, 255));
        this->addChild(m_seasonTitle, 10);

        m_levelSpriteFrameNorm = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_level_pass.png");
        m_levelSpriteFrameGray = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_level.png");
        m_levelSprite = CCSprite::createWithSpriteFrame(m_levelSpriteFrameGray);
        m_levelSprite->setAnchorPoint(CCPoint(0, 0));
        m_levelSprite->setPosition(CCPoint(0, 0));
        this->addChild(m_levelSprite, 0);

        for (int i = 0; i < MAX_STAR_COUNT; i++) {
            m_star[i] = CCSprite::createWithSpriteFrameName("icon_star.png");
            m_star[i]->setAnchorPoint(CCPoint(0.5, 0.5));
            m_star[i]->setVisible(false);
            this->addChild(m_star[i], 100);
        }

        bRet = true;
    } while (0);

    return bRet;
}

void LevelNode::initWithLevel(Level* level) {
    if (level == NULL || m_level == level) {
        m_level = level;
        return;
    }

    m_level = level;
    m_label->setString(CCString::createWithFormat("%d", m_level->level())->getCString());
    if (m_level->locked()) {
        m_levelSprite->setDisplayFrame(m_levelSpriteFrameGray);
        hideStar();
    }
    else {
        m_levelSprite->setDisplayFrame(m_levelSpriteFrameNorm);
        updateStar(m_level->starCount());
    }
}

void LevelNode::updateLevelUI() {
    if (m_level == NULL)
        return;

    /*if (m_seasonTitle->getString() == "")
        m_seasonTitle->setVisible(false);*/
    updateStar(m_level->starCount());
}

void LevelNode::setSeasonTitle(const string& title) {
    m_seasonTitle->setString(title.c_str());
}

void LevelNode::updateStar(int star) {
    hideStar();
    if (star == 1) {
        m_star[0]->setVisible(true);
        m_star[0]->setPosition(CCPoint(LEVELNODE_WIDTH/2, 10));
    }
    else if (star == 2) {
        m_star[0]->setVisible(true);
        m_star[0]->setPosition(CCPoint(LEVELNODE_WIDTH/2-20, 15));
        m_star[1]->setVisible(true);
        m_star[1]->setPosition(CCPoint(LEVELNODE_WIDTH/2+20, 15));
    }
    else if (star == 3) {
        m_star[0]->setVisible(true);
        m_star[0]->setPosition(CCPoint(LEVELNODE_WIDTH/2-35, 20));
        m_star[1]->setVisible(true);
        m_star[1]->setPosition(CCPoint(LEVELNODE_WIDTH/2, 10));
        m_star[2]->setVisible(true);
        m_star[2]->setPosition(CCPoint(LEVELNODE_WIDTH/2+35, 20));
    }
}

void LevelNode::hideStar() {
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        m_star[i]->setVisible(false);
    }
}

