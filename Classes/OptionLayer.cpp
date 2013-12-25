/*
 * OptionLayer.cpp
 *
 *  Created on: 2013-7-14
 *      Author: maxing
 */

#include "OptionLayer.h"
#include "GameScene.h"

using namespace cocos2d;

OptionLayer::OptionLayer() {
    m_option = "";
    m_isAnswer = false;
}

OptionLayer::~OptionLayer() {
}

bool OptionLayer::init() {
    bool bRet = false;
    do {
        CCLayerColor::initWithColor(ccc4(233,233,122,255));

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        m_optionLabel = CCLabelBMFont::create(m_option, "arial.ttf");

        bRet = true;
    } while (0);

    return bRet;
}

}
