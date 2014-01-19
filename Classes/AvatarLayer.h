/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: AvatarLayer.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:12:13 $
 * @brief
 *
 ******************************************************************/

#ifndef AvatarLayer_H_
#define AvatarLayer_H_

#include "Config.h"
#include <cocos2d.h>

USING_NS_CC;

class AvatarLayer: public cocos2d::CCLayer {
public:
    AvatarLayer();
    virtual ~AvatarLayer();
    CREATE_FUNC(AvatarLayer);
    virtual bool init();

    bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void registerWithTouchDispatcher();

private:
    void unpackAvatar();
    void packAvatar();
    void showSelectAvatar();
private:
    CCSprite*   m_avatarList[MAX_AVATAR_COUNT];
    CCSprite*   m_avatarFrame;

    CCPoint     m_avatarCenter;
    int         m_showId;
    bool        m_isShowAll;
};

#endif /* AvatarLayer_H_ */
