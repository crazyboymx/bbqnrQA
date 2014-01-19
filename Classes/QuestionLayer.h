/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: QuestionLayer.h
 * $Id: QuestionLayer.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:46 $
 * @brief
 *
 ******************************************************************/

#ifndef __QuestionLayer_H_
#define __QuestionLayer_H_

#include "Config.h"
#include <cocos2d.h>
#include <string>

USING_NS_CC;
using namespace std;

class QuestionLayer;

class QuestionLayer : public CCLayer {
public:
    QuestionLayer();
    virtual ~QuestionLayer();
    CREATE_FUNC(QuestionLayer);
    virtual bool init();

    void setQuestionTitle(string title);
    void updateStar(int star);
    void initStar();

private:
    void newStarCollectAnimation(CCSprite* origin);
private:
    string          m_title;
    int             m_starCnt;
    CCLabelTTF*     m_titleLabel;
    CCSprite*       m_bgSprite;
    CCSprite*       m_star[MAX_STAR_COUNT];
    CCSpriteFrame*  m_star_norm[MAX_STAR_COUNT];
    CCSpriteFrame*  m_star_gray[MAX_STAR_COUNT];
};

#endif // __QuestionLayer_H_
