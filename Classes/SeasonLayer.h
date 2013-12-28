/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: SeasonLayer.h
 * $Id: SeasonLayer.h v 1.0 2013-12-26 21:48:30 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:52:58 $
 * @brief
 *
 ******************************************************************/

#ifndef __SEASONLAYER_H_
#define __SEASONLAYER_H_

#include <cocos2d.h>
#include "Season.h"

USING_NS_CC;
using namespace std;

class SeasonLayer : public CCLayer {
public:
    SeasonLayer();
    virtual ~SeasonLayer();
    CREATE_FUNC(SeasonLayer);
    virtual bool init();
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void registerWithTouchDispatcher();

    void initWithSeason(Season* season);
private:
    void initLevelNode();
private:
    Season* m_season;
    CCLabelTTF* m_titleLabel;
    CCArray* m_levelNodeArray;
};

#endif // __SEASONLAYER_H_
