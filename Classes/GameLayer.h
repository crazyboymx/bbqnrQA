/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.h
 * $Id: GameLayer.h v 1.0 2013-12-26 01:08:43 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 14:54:33 $
 * @brief
 *
 ******************************************************************/

#ifndef __GAMELAYER_H_
#define __GAMELAYER_H_

#include <cocos2d.h>
#include "OptionLayer.h"
#include "Level.h"

using namespace std;
USING_NS_CC;

class GameLayer : public CCLayer, private OptionObserver {
public:
    GameLayer();
    virtual ~GameLayer();
    CREATE_FUNC(GameLayer);
    virtual bool init();

    void setLevel(Level* l) {
        m_level = l;
        l->shuffleQuestion();
        setQuestion(m_level->nextQuesion());}
    void setQuestion(Question question);

    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void registerWithTouchDispatcher();

private:
    void optionSelected(OptionLayer* option);

private:
    Level* m_level;
    Question m_question;

    OptionLayer*    m_option_a;
    OptionLayer*    m_option_b;
    OptionLayer*    m_option_c;
    OptionLayer*    m_option_d;
    CCLabelTTF*     m_questionLabel;
};

#endif // __GAMELAYER_H_
