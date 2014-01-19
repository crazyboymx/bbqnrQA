/*
 * BackGroundLayer.cpp
 *
 *  Created on: 2013-7-14
 *      Author: maxing
 */

#include "Config.h"
#include "BackGroundLayer.h"

using namespace cocos2d;

BackGroundLayer::BackGroundLayer() {
}

BackGroundLayer::~BackGroundLayer() {
}

bool BackGroundLayer::init() {
    bool bRet = false;
    do {
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(0,0,0,255) ) );

        m_mapBGSprite0 = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("map_0.png"));
        m_mapBGSprite0->setPosition(CCPoint(0, 0));
        m_mapBGSprite0->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_mapBGSprite0);

        m_mapBGSprite1 = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("map_1.png"));
        m_mapBGSprite1->setPosition(CCPoint(0, 0));
        m_mapBGSprite1->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_mapBGSprite1);

        m_mapBGSprite2 = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("map_1.png"));
        m_mapBGSprite2->setPosition(CCPoint(0, 0));
        m_mapBGSprite2->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_mapBGSprite2);

        m_mapCloudSprite1 = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("map_cloud.png"));
        m_mapCloudSprite1->setPosition(CCPoint(0, 0));
        m_mapCloudSprite1->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_mapCloudSprite1);

        m_mapCloudSprite2 = CCSprite::createWithTexture(
                CCTextureCache::sharedTextureCache()->textureForKey("map_cloud.png"));
        m_mapCloudSprite2->setPosition(CCPoint(0, 0));
        m_mapCloudSprite2->setAnchorPoint(CCPoint(0, 0));
        this->addChild(m_mapCloudSprite2);
        scrollMapTo(0);
        scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void BackGroundLayer::update(float delta) {
    //CCLog("BackGroundLayer::update, delta %0.2f", delta);
    float dy = MAP_CLOUD_SPPED * delta;
    float pos = m_mapCloudSprite1->getPositionY()+dy;
    if (pos > MAP_HEIGHT)
        pos -= MAP_HEIGHT;
    m_mapCloudSprite1->setPositionY(pos);
    m_mapCloudSprite2->setPositionY(pos-MAP_HEIGHT);
}

void BackGroundLayer::scrollMapTo(int y) {
    int height = MAP_HEIGHT;
    if (y <= height) {
        m_mapBGSprite0->setVisible(true);
        m_mapBGSprite2->setVisible(false);
        m_mapBGSprite0->setPositionY(-y);
        m_mapBGSprite1->setPositionY(height-y);
    }
    else {
        y -= (y / height) * height;
        m_mapBGSprite0->setVisible(false);
        m_mapBGSprite2->setVisible(true);
        m_mapBGSprite1->setPositionY(-y);
        m_mapBGSprite2->setPositionY(height-y);
    }
}
