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
        CCSize contentSize(400, 100);

        m_optionLabel = CCLabelBMFont::create(m_option, "arial.ttf");
        m_optionLabel->setAnchorPoint(0.5, 0.5);
        m_optionLabel->setPosition(contentSize.width/2, contentSize.height/2);
        this->addChild(m_optionLabel);
        this->setContentSize(contentSize);

        bRet = true;
    } while (0);

    return bRet;
}

void setOption(const char* option, bool isAnswer) {
    m_option = option;
    m_isAnswer = isAnswer;
    m_optionLabel->setCString(option);
}

}
