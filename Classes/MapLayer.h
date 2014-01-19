/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MapLayer.h
 * $Id: MapLayer.h v 1.0 2013-12-26 21:48:30 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:52:58 $
 * @brief
 *
 ******************************************************************/

#ifndef __MapLayer_H_
#define __MapLayer_H_

#include "Config.h"
#include <cocos2d.h>

USING_NS_CC;
using namespace std;

class BackGroundLayer;
class AvatarLayer;
class LevelNode;
class Season;

class MapLayer : public CCLayer {
public:
    static MapLayer* sharedLayer();

    MapLayer();
    virtual ~MapLayer();
    CREATE_FUNC(MapLayer);
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent *event);
    virtual void registerWithTouchDispatcher();

private:
    void initSeasons();
    void updateMap();
private:
    BackGroundLayer*    m_bg;
    AvatarLayer*        m_avatar;
    CCSprite*           m_settingSprite;
    LevelNode*          m_levelPool[MAP_MAX_LEVEL];
    Season*             m_seasons[MAX_SEASON];
    int                 m_seasonStartLevel[MAX_SEASON];
    int                 m_totalLevel;
    int                 m_currentLevel;

    int     m_bgPosY;
    int     m_MaxY;
    bool    m_touching;

    static MapLayer* m_sharedLayer;
};

#endif // __MapLayer_H_
