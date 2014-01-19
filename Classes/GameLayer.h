/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.h
 * $Id: GameLayer.h v 1.0 2013-12-26 01:08:43 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 18:40:08 $
 * @brief
 *
 ******************************************************************/

#ifndef __GAMELAYER_H_
#define __GAMELAYER_H_

#include <cocos2d.h>
#include "OptionLayer.h"
#include "QuestionLayer.h"
#include "Level.h"

using namespace std;
USING_NS_CC;

class GameLayer : public CCLayer, private OptionObserver {
public:
    static GameLayer* sharedLayer();

    GameLayer();
    virtual ~GameLayer();
    CREATE_FUNC(GameLayer);
    virtual bool init();

    void initWithLevel(Level* lvl);
    void startLevel();

    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void registerWithTouchDispatcher();

private:
    void onOptionSelected(OptionLayer* option);
    void nextQuestion();
    void updateQuestionUI();
    void answerCorrect();
    void answerWrong();
    void levelComplete();
    void levelPass();
    void levelFail();

    void questionEndAnimation();
    void questionStartAnimation();

private:
    Level* m_level;
    bool m_levelPassed;
    Question m_question;

    OptionLayer*    m_option_a;
    OptionLayer*    m_option_b;
    OptionLayer*    m_option_c;
    OptionLayer*    m_option_d;
    QuestionLayer*  m_questionLayer;
    CCSprite*       m_layerBGSprite;

    CCPoint         m_questionLayerPosition;
    CCPoint         m_optionAPosition;
    CCPoint         m_optionBPosition;
    CCPoint         m_optionCPosition;
    CCPoint         m_optionDPosition;

    static GameLayer* m_sharedLayer;
};

#endif // __GAMELAYER_H_
