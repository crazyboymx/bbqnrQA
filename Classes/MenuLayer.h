/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:12:13 $
 * @brief
 *
 ******************************************************************/

#ifndef MenuLayer_H_
#define MenuLayer_H_

#include <cocos2d.h>

USING_NS_CC;

class MenuLayer: public cocos2d::CCLayer {
public:
    MenuLayer();
    virtual ~MenuLayer();
    CREATE_FUNC(MenuLayer);
    virtual bool init();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent);

    void onStartClicked();
private:
    void darenxiuAppear();
    void darenxiuAnimation();
    void darenxiuSound();
    void showDa();
    void showRen();
    void showXiu();
private:
    CCSprite*   m_bgSprite;
    CCSprite*   m_daSprite;
    CCSprite*   m_renSprite;
    CCSprite*   m_xiuSprite;
    CCSprite*   m_startSprite;
};

#endif /* MenuLayer_H_ */
