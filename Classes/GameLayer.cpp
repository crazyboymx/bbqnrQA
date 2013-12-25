/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.cpp
 * $Id: GameLayer.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 17:04:25 $
 * @brief
 *
 ******************************************************************/

#include "GameLayer.h"
#include <cstdlib>
#include <algorithm>

using namespace cocos2d;

GameLayer::GameLayer() {
}

GameLayer::~GameLayer() {
}

bool GameLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCLog("origin %0.2f, %0.2f, visibleSize %0.2f, %0.2f", origin.x, origin.y, visibleSize.width, visibleSize.height);

        m_option_a = OptionLayer::create();
        CCSize optionContentSize = m_option_a->getContentSize();
        m_option_a->ignoreAnchorPointForPosition(false);
        m_option_a->setPosition(origin.x+visibleSize.width/2, origin.y+(optionContentSize.height+50)*3+100);
        m_option_a->setAnchorPoint(CCPoint(0.5f, 0.0f));
        this->addChild(m_option_a);
        m_option_a->addObserver(this);

        m_option_b = OptionLayer::create();
        m_option_b->ignoreAnchorPointForPosition(false);
        m_option_b->setPosition(origin.x+visibleSize.width/2, origin.y+(optionContentSize.height+50)*2+100);
        m_option_b->setAnchorPoint(CCPoint(0.5f, 0.0f));
        this->addChild(m_option_b);
        m_option_b->addObserver(this);

        m_option_c = OptionLayer::create();
        m_option_c->ignoreAnchorPointForPosition(false);
        m_option_c->setPosition(origin.x+visibleSize.width/2, origin.y+(optionContentSize.height+50)*1+100);
        m_option_c->setAnchorPoint(CCPoint(0.5f, 0.0f));
        this->addChild(m_option_c);
        m_option_c->addObserver(this);

        m_option_d = OptionLayer::create();
        m_option_d->ignoreAnchorPointForPosition(false);
        m_option_d->setPosition(origin.x+visibleSize.width/2, origin.y+(optionContentSize.height+50)*0+100);
        m_option_d->setAnchorPoint(CCPoint(0.5f, 0.0f));
        this->addChild(m_option_d);
        m_option_d->addObserver(this);

        m_questionLabel = CCLabelTTF::create("", "Marker Felt.ttf", 40,
            CCSizeMake(visibleSize.width, 300), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        m_questionLabel->setAnchorPoint(CCPoint(0.0, 0.0));
        m_questionLabel->setPosition(CCPoint(origin.x, origin.y+(optionContentSize.height+50)*5+100));
        this->addChild(m_questionLabel);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::optionSelected(OptionLayer* option) {
    if (option->isAnswer()) {
    }
    else {
    }
}

void GameLayer::setQuestion(string question, Option option) {
    m_question = question;
    m_option = option;
    m_questionLabel->setString(question.c_str());
    int opt[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        int s = rand() % 4;
        int tmp = opt[i];
        opt[i] = opt[s];
        opt[s] = tmp;
    }

    string optStr;
    optStr = "A. "+option[opt[0]];
    m_option_a->setOption(optStr, opt[0] == option.answer);
    optStr = "B. "+option[opt[1]];
    m_option_b->setOption(optStr, opt[1] == option.answer);
    optStr = "C. "+option[opt[2]];
    m_option_c->setOption(optStr, opt[2] == option.answer);
    optStr = "D. "+option[opt[3]];
    m_option_d->setOption(optStr, opt[3] == option.answer);
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCLog("touch in GameLayer");
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}
