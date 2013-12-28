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
    m_levelSprite = NULL;
}

LevelNode::~LevelNode() {
}

bool LevelNode::init() {
    bool bRet = false;
    do {
        CCNode::init();

        //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCSize contentSize(LEVELNODE_WIDTH, LEVELNODE_HEIGHT);
        this->setContentSize(contentSize);

        m_levelLabel = CCLabelTTF::create("", "Marker Felt.ttf", 40,
            contentSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        m_levelLabel->setAnchorPoint(CCPoint(0.5, 0.5));
        m_levelLabel->setPosition(CCPoint(contentSize.width/2, contentSize.height/2));
        this->addChild(m_levelLabel);

        bRet = true;
    } while (0);

    return bRet;
}

void LevelNode::initWithLevel(Level* level) {
    m_level = level;
    if (m_level != NULL)
        m_levelLabel->setString(
                CCString::createWithFormat("%d", m_level->level())->getCString());
}

