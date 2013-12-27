/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: SeasonLayer.cpp
 * $Id: SeasonLayer.cpp v 1.0 2013-12-26 21:50:35 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:52:39 $
 * @brief
 *
 ******************************************************************/

#include "SeasonLayer.h"

SeasonLayer::SeasonLayer() {
    m_season = NULL;
}

SeasonLayer::~SeasonLayer() {
}

bool SeasonLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void SeasonLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
}

void SeasonLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void SeasonLayer::setSeason(Season* season) {
    m_season = season;
}

