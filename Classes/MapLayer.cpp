/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MapLayer.cpp
 * $Id: MapLayer.cpp v 1.0 2013-12-26 21:50:35 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:52:39 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "MapLayer.h"
#include "BackGroundLayer.h"
#include "AvatarLayer.h"
#include "LevelNode.h"
#include "GameLayer.h"
#include "SettingLayer.h"
#include "Season.h"

CCPoint g_mapSlots[MAP_MAX_LEVEL] = {
    CCPoint(377,147),
    CCPoint(180,292),
    CCPoint(330,458),
    CCPoint(535,588),
    CCPoint(340,745),
    CCPoint(125,875),
    CCPoint(390,915),
    CCPoint(458,1130),
    CCPoint(256,1275),
    CCPoint(320,1487),
    CCPoint(377,147) + CCPoint(0, 1540),
    CCPoint(180,292) + CCPoint(0, 1540),
    CCPoint(330,458) + CCPoint(0, 1540),
    CCPoint(535,588) + CCPoint(0, 1540),
    CCPoint(340,745) + CCPoint(0, 1540),
    CCPoint(125,875) + CCPoint(0, 1540),
    CCPoint(390,915) + CCPoint(0, 1540),
    CCPoint(458,1130) + CCPoint(0, 1540),
    CCPoint(256,1275) + CCPoint(0, 1540),
    CCPoint(320,1487) + CCPoint(0, 1540)
};

MapLayer* MapLayer::m_sharedLayer = NULL;

MapLayer* MapLayer::sharedLayer() {
    if (m_sharedLayer == NULL) {
        m_sharedLayer = MapLayer::create();
        m_sharedLayer->retain();
    }

    return m_sharedLayer;
}

MapLayer::MapLayer() {
}

MapLayer::~MapLayer() {
}

bool MapLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();
        m_bgPosY = 0;

        /*m_titleLabel = CCLabelTTF::create("", "Marker Felt.ttf", 40,
            CCSize(visibleSize.width, SEASON_TITLE_HEIGHT), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        m_titleLabel->setAnchorPoint(CCPoint(0.5, 0));
        m_titleLabel->setPosition(CCPoint(visibleSize.width/2 + origin.x, visibleSize.height - SEASON_TITLE_HEIGHT + origin.y));
        this->addChild(m_titleLabel);*/

        m_bg = BackGroundLayer::create();
        m_bg->setAnchorPoint(CCPoint(0, 0));
        m_bg->setPosition(CCPoint(0, 0));
        this->addChild(m_bg, 0);

        m_settingSprite = CCSprite::createWithSpriteFrameName("icon_setting.png");
        m_settingSprite->setAnchorPoint(CCPoint(0, 0));
        m_settingSprite->setPosition(CCPoint(0, 0));
        this->addChild(m_settingSprite, 1000);

        for (int i = 0; i < MAP_MAX_LEVEL; i++) {
            m_levelPool[i] = LevelNode::create();
            m_levelPool[i]->setAnchorPoint(CCPoint(0.5, 0.5));
            m_levelPool[i]->setPosition(g_mapSlots[i % MAP_MAX_LEVEL]);
            this->addChild(m_levelPool[i], 10);
        }

        m_avatar = AvatarLayer::create();
        m_avatar->ignoreAnchorPointForPosition(false);
        m_avatar->setAnchorPoint(CCPoint(0.5, 0));
        m_avatar->setPosition(m_levelPool[m_currentLevel % MAP_MAX_LEVEL]->getPosition()+CCPoint(0, 25));
        this->addChild(m_avatar, 100);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void MapLayer::onEnterTransitionDidFinish() {
    m_bg->scheduleUpdate();
    initSeasons();
    updateMap();
}

bool MapLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = convertToNodeSpace(touch->getLocation());
    if (!boundingBox().containsPoint(location))
        return false;

    m_touching = true;
    return true;
}

void MapLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = convertToNodeSpace(touch->getLocation());
    if (!boundingBox().containsPoint(location) || !m_touching)
        return;

    m_bgPosY -= touch->getDelta().y;
    m_bgPosY = min(max(0, m_bgPosY), m_MaxY);
    updateMap();
}

void MapLayer::ccTouchEnded(CCTouch* touch, CCEvent* pEvent) {
    CCPoint location = convertToNodeSpace(touch->getLocation());
    CCPoint startLoc = convertToNodeSpace(touch->getStartLocation());
    if (!boundingBox().containsPoint(location))
        return;

    m_touching = false;
    if (abs(startLoc.x - location.x) >= MIN_MOVE_GAP || abs(startLoc.y - location.y) >= MIN_MOVE_GAP)
        return;

    if (m_settingSprite->boundingBox().containsPoint(location)) {
        SettingLayer::sharedLayer()->show();
        return;
    }

    for (int i = 0; i < MAP_MAX_LEVEL; i++) {
        LevelNode* lvlNode = m_levelPool[i];
        Level* lvl = lvlNode->level();
        CCRect r = lvlNode->boundingBox();
        if (lvlNode->boundingBox().containsPoint(location)) {
            if (lvl == NULL) {
                // TODO: add continue hint.
            }
            else if (lvl->locked()) {
                // TODO: add locked level hit effect.
            }
            else {
                GameLayer* layer = GameLayer::sharedLayer();
                layer->initWithLevel(lvl);
                layer->startLevel();
                CCScene* pScene = CCScene::create();
                pScene->addChild(layer);
                CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
                CCDirector::sharedDirector()->replaceScene(transitionScene);
            }
            break;
        }
    }
}

void MapLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void MapLayer::initSeasons() {
    int startLevel = 1;
    m_totalLevel = 0;
    m_currentLevel = 0;
    for (int i = 0; i < MAX_SEASON; i++) {
        m_seasons[i] = new Season((Season::SeasonId)i);
        m_seasons[i]->initLevels(startLevel);
        m_seasonStartLevel[i] = startLevel;
        startLevel += m_seasons[i]->levelCount();
    }
    m_totalLevel = startLevel - 1;
    m_MaxY = (m_totalLevel / LEVEL_PER_MAP) * MAP_HEIGHT + g_mapSlots[m_totalLevel % LEVEL_PER_MAP].y + 100;
    m_MaxY -= CCDirector::sharedDirector()->getVisibleSize().height;
}

void MapLayer::updateMap() {
    m_bg->scrollMapTo(m_bgPosY);
    int dy = m_bgPosY - (m_bgPosY / MAP_HEIGHT) * MAP_HEIGHT;
    int level = (m_bgPosY / MAP_HEIGHT) * LEVEL_PER_MAP + 1;
    int season = Season::Season_1;
    for (int i = 0; i < MAX_SEASON; i++) {
        if (level >= m_seasonStartLevel[i] && level < m_seasonStartLevel[i+1])
            season = i;
    }

    int seasonLevelCount = m_seasons[season]->levelCount();
    for (int i = 0; i < MAP_MAX_LEVEL; i++) {
        m_levelPool[i]->setPosition(g_mapSlots[i]+CCPoint(0, -dy));
        if (level > m_seasonStartLevel[season] + seasonLevelCount) {
            season++;
            seasonLevelCount = m_seasons[season]->levelCount();
        }
        if (level == m_seasonStartLevel[season])
            m_levelPool[i]->setSeasonTitle(m_seasons[season]->title());
        else
            m_levelPool[i]->setSeasonTitle("");
        m_levelPool[i]->initWithLevel(m_seasons[season]->level(level));
        m_levelPool[i]->updateLevelUI();
        level++;
    }
    m_avatar->setPosition(m_levelPool[m_currentLevel % MAP_MAX_LEVEL]->getPosition()+CCPoint(0, 25));
}
