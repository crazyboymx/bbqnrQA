#include "Config.h"
#include "AppDelegate.h"
#include "Season.h"
#include "Record.h"
#include "MenuLayer.h"
#include "AudioManager.h"
#include "SettingLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

    CCSize designSize = CCSizeMake(DESIGNED_WIDTH, DESIGNED_HEIGHT);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);

    std::vector<std::string> searchPaths;
    searchPaths.push_back("fonts");
    searchPaths.push_back("sounds");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    CCSpriteFrameCache* cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("batch.plist");
    CCTextureCache* texCacher = CCTextureCache::sharedTextureCache();
    texCacher->addImage("star_particle.png");
    texCacher->addImage("main_bg.png");
    texCacher->addImage("game_bg.png");
    texCacher->addImage("map_0.png");
    texCacher->addImage("map_1.png");
    texCacher->addImage("map_end.png");
    texCacher->addImage("map_cloud.png");

    AudioManager* am = AudioManager::instance();
    am->preloadBackgroundMusic("background.wav");
    am->preloadEffect("chainDown.mp3");
    am->preloadEffect("chainUp.mp3");
    am->preloadEffect("click.wav");
    am->preloadEffect("clickButton.ogg");
    am->preloadEffect("correct.mp3");
    am->preloadEffect("wrong.mp3");
    am->preloadEffect("levelLose.mp3");
    am->preloadEffect("levelPass.mp3");
    am->preloadEffect("levelUnlock.wav");
    am->preloadEffect("sealPress.mp3");
    am->preloadEffect("walk.mp3");
    am->setBackgroundMusic("background.mp3");

    SettingLayer::sharedLayer()->updateSettingLayer();
    am->setBackgroundMute(SettingLayer::sharedLayer()->isBgMusicMute());
    am->setSoundEffectMute(SettingLayer::sharedLayer()->isEffectMute());
    // turn on display FPS
    pDirector->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = CCScene::create();

    MenuLayer* menu = MenuLayer::create();
    pScene->addChild(menu);

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    AudioManager::instance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    AudioManager::instance()->resumeBackgroundMusic();
}
