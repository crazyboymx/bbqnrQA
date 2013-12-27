/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: OptionLayer.cpp
 * $Id: OptionLayer.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:45 $
 * @brief
 *
 ******************************************************************/

#include "OptionLayer.h"
#include <algorithm>

OptionLayer::OptionLayer() {
    m_option = "";
    m_isAnswer = false;
    m_observers;
}

OptionLayer::~OptionLayer() {
}

bool OptionLayer::init() {
    bool bRet = false;
    do {
        CCLayerColor::initWithColor(ccc4(233,233,122,255));

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCSize contentSize(visibleSize.width-100, 100);

        m_optionLabel = CCLabelTTF::create("", "Marker Felt.ttf", 40,
            contentSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        m_optionLabel->setAnchorPoint(CCPoint(0.0, 0.0));
        m_optionLabel->setPosition(CCPoint(0.0, 0.0));
        this->addChild(m_optionLabel);
        this->setContentSize(contentSize);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void OptionLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();
    if (!this->boundingBox().containsPoint(location))
        return;

    if (m_isAnswer)
        this->setColor(ccc3(0, 255, 0));
    else
        this->setColor(ccc3(255, 0, 0));
    vector<OptionObserver*>::iterator pos = m_observers.begin();
    for (;pos != m_observers.end(); ++pos) {
        (*pos)->onOptionSelected(this);
    }
}

void OptionLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void OptionLayer::addObserver(OptionObserver* observer) {
    m_observers.push_back(observer);
}

void OptionLayer::removeObserver(OptionObserver* observer) {
    m_observers.erase(remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void OptionLayer::setOption(string option, bool isAnswer) {
    m_option = option;
    m_isAnswer = isAnswer;
    m_optionLabel->setString(option.c_str());
    this->setColor(ccc3(233, 233, 122));
}

