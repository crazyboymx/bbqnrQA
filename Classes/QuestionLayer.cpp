/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: QuestionLayer.cpp
 * $Id: QuestionLayer.cpp v 1.0 2013-12-26 01:08:55 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:45 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "QuestionLayer.h"
#include "AudioManager.h"
#include <algorithm>

QuestionLayer::QuestionLayer() {
    m_title = "";
    m_starCnt = 0;
}

QuestionLayer::~QuestionLayer() {
}

bool QuestionLayer::init() {
    bool bRet = false;
    do {
        CCLayer::init();

        CCSize contentSize(QUESTIONLAYER_CONTENT_WIDTH, QUESTIONLAYER_CONTENT_HEIGHT);
        this->setContentSize(contentSize);

        m_titleLabel = CCLabelTTF::create("", "Marker Felt.ttf", QUESTIONLAYER_TITLE_SIZE,
            CCSize(QUESTIONLAYER_TITLE_WIDTH, QUESTIONLAYER_TITLE_HEIGHT),
            kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        m_titleLabel->setAnchorPoint(CCPoint(0.0, 0.0));
        m_titleLabel->setPosition(CCPoint(30.0, 45.0));
        this->addChild(m_titleLabel, 100);

        m_bgSprite = CCSprite::createWithSpriteFrameName("question_bg.png");
        m_bgSprite->setAnchorPoint(CCPoint(0.0, 0.0));
        m_bgSprite->setPosition(CCPoint(0.0, 0.0));
        this->addChild(m_bgSprite, 10);

        for (int i = 0; i < MAX_STAR_COUNT; i++) {
            float x = contentSize.width / 2 + (i - MAX_STAR_COUNT/2) * 50;
            m_star[i] = CCSprite::createWithSpriteFrameName("star.png");
            m_star[i]->setPosition(CCPoint(x, 250));
            m_star[i]->setAnchorPoint(CCPoint(0.5, 0.5));
            m_star_gray[i] = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("star_gray.png");
            m_star_gray[i]->retain();
            m_star_norm[i] = m_star[i]->displayFrame();
            m_star_norm[i]->retain();
            m_star[i]->setDisplayFrame(m_star_gray[i]);
            m_star[i]->setScale(0.5);
            this->addChild(m_star[i], 100);
        }

        //this->setTouchEnabled(true);
        //this->setKeypadEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void QuestionLayer::setQuestionTitle(string title) {
    m_title = title;
    m_titleLabel->setString(title.c_str());
}

void QuestionLayer::updateStar(int star) {
    if (m_starCnt >= star)
        return;

    star = min(star, MAX_STAR_COUNT);
    for (int i = m_starCnt; i < star; i++) {
        m_star[i]->setDisplayFrame(m_star_norm[i]);
        newStarCollectAnimation(m_star[i]);
    }
    m_starCnt = star;
}

void QuestionLayer::initStar() {
    m_starCnt = 0;
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        m_star[i]->setDisplayFrame(m_star_gray[i]);
    }
}

void QuestionLayer::newStarCollectAnimation(CCSprite* origin) {
    CCParticleExplosion *emitter = CCParticleExplosion::createWithTotalParticles(10);
    emitter->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("star_particle.png"));
    emitter->setPosition(origin->getPosition());
    emitter->setLife(1);
    emitter->setLifeVar(0.2);
    emitter->setStartColor(ccc4f(1.0f, 1.0f, 1.0f, 1.0f));
    emitter->setStartColorVar(ccc4f(0.0f, 0.0f, 0.0f, 0.0f));
    emitter->setEndColor(ccc4f(1.0f, 1.0f, 1.0f, 1.0f));
    emitter->setEndColorVar(ccc4f(0.0f, 0.0f, 0.0f, 0.0f));
    AudioManager::instance()->playEffect("sealPress.mp3");
    this->addChild(emitter, 1000);
}

