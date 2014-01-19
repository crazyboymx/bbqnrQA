/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: SeasonLayer.cpp
 * $Id: SeasonLayer.cpp v 1.0 2013-12-26 21:50:35 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:52:39 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "SeasonLayer.h"
#include "LevelNode.h"
#include "GameLayer.h"

#define SEASON_TITLE_HEIGHT 100

SeasonLayer::SeasonLayer() {
    m_season = NULL;
    m_levelNodeArray = CCArray::create();
    m_levelNodeArray->retain();
}

SeasonLayer::~SeasonLayer() {
    m_levelNodeArray->release();
}

bool SeasonLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        m_titleLabel = CCLabelTTF::create("", "Marker Felt.ttf", 40,
            CCSize(visibleSize.width, SEASON_TITLE_HEIGHT), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        m_titleLabel->setAnchorPoint(CCPoint(0.5, 0));
        m_titleLabel->setPosition(CCPoint(visibleSize.width/2 + origin.x, visibleSize.height - SEASON_TITLE_HEIGHT + origin.y));
        this->addChild(m_titleLabel);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void SeasonLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();

    CCObject *obj = NULL;
    LevelNode* lvl = NULL;
    CCARRAY_FOREACH(m_levelNodeArray, obj) {
        LevelNode* lvl = (LevelNode*)obj;
        if (lvl->boundingBox().containsPoint(location)) {
            GameLayer* layer = GameLayer::sharedLayer();
            layer->initWithLevel(lvl->level());
            layer->startLevel();
            CCScene* pScene = CCScene::create();
            pScene->addChild(layer);
            CCDirector::sharedDirector()->replaceScene(pScene);
            break;
        }
    }
}

void SeasonLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void SeasonLayer::initWithSeason(Season* season) {
    m_season = season;
    if (m_season != NULL)
        m_titleLabel->setString(m_season->title().c_str());
    initLevelNode();
}

void SeasonLayer::initLevelNode() {
    if (m_season == NULL)
        return;
    int levelCount = m_season->levelCount();
    int lvlNum = 1;
    int row = 1;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    while (lvlNum <= levelCount) {
        for (int i = 0; i < 4; i++) {
            Level* lvl = m_season->level(lvlNum);
            LevelNode* ln = LevelNode::create();
            ln->initWithLevel(lvl);
            ln->setPosition(CCPoint(i * LEVELNODE_WIDTH + origin.x,
                        visibleSize.height - SEASON_TITLE_HEIGHT - row * LEVELNODE_HEIGHT + origin.y));
            ln->setAnchorPoint(CCPoint(0.0f, 0.0f));
            this->addChild(ln);
            m_levelNodeArray->addObject(ln);
            lvlNum++;
        }
        row++;
    }
    //CCLog("levelCount: %d, childCount: %d", levelCount, this->getChildrenCount());
}

