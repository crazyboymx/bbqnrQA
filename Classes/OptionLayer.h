/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: OptionLayer.h
 * $Id: OptionLayer.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:46 $
 * @brief
 *
 ******************************************************************/

#ifndef __OPTIONLAYER_H_
#define __OPTIONLAYER_H_

#include <cocos2d.h>
#include "Question.h"
#include <vector>

USING_NS_CC;
using namespace std;

class OptionLayer;

class OptionObserver {
public:
    virtual ~OptionObserver() { }

    virtual void onOptionSelected(OptionLayer* option) = 0;
};

class OptionLayer : public CCLayer {
public:
    OptionLayer();
    virtual ~OptionLayer();
    CREATE_FUNC(OptionLayer);
    virtual bool init();
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void registerWithTouchDispatcher();

    void addObserver(OptionObserver* observer);
    void removeObserver(OptionObserver* observer);

    void setOption(string option, bool isAnswer);
    bool isAnswer() const { return m_isAnswer; }

    void showAnswerAnimation();

private:
    string          m_option;
    bool            m_isAnswer;
    CCLabelTTF*     m_optionLabel;
    CCSprite*       m_bgSprite;
    CCSprite*       m_correctSprite;
    CCSprite*       m_wrongSprite;
    vector<OptionObserver*> m_observers;
};

#endif // __OPTIONLAYER_H_
