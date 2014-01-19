/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: SettingLayer.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:12:13 $
 * @brief
 *
 ******************************************************************/

#ifndef SettingLayer_H_
#define SettingLayer_H_

#include <cocos2d.h>

USING_NS_CC;

class SettingLayer: public cocos2d::CCLayer {
public:
    static SettingLayer* sharedLayer();

    SettingLayer();
    virtual ~SettingLayer();
    CREATE_FUNC(SettingLayer);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent *event);
    virtual void registerWithTouchDispatcher();
    virtual void keyBackClicked();

    bool isBgMusicMute() const { return m_bgMusicMute; }
    bool isEffectMute() const { return m_effectMute; }
    int avatarId() const { return m_avatarId; }
    void setAvatarId(int id);

    void show();
    void updateSettingLayer();
private:
    void loadSettings();
    void saveSettings();
    void runShowAnimation();
    void runHideAnimation();
private:
    static SettingLayer* m_sharedLayer;
    bool m_bgMusicMute;
    bool m_effectMute;
    int  m_avatarId;

    CCSprite*   m_bgSprite;
    CCLabelTTF* m_musicLabel;
    CCLabelTTF* m_effectLabel;
    CCSprite*   m_musicSelectSprite;
    CCSprite*   m_effectSelectSprite;
    CCSprite*   m_musicSelectBgSprite;
    CCSprite*   m_effectSelectBgSprite;
    CCSprite*   m_linesprite1;
    CCSprite*   m_linesprite2;
    CCSprite*   m_backSprite;
    CCNode*     m_container;
};

#endif /* SettingLayer_H_ */
