/*
 * AudioManager.cpp
 *
 *  Created on: 2014-1-7
 *      Author: maxing
 */

#include "Config.h"
#include "AudioManager.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

AudioManager* AudioManager::g_instance = NULL;

AudioManager* AudioManager::instance() {
    if (g_instance == NULL)
        g_instance = new AudioManager();

    return g_instance;
}

void AudioManager::setBackgroundMute(bool mute) {
    m_bgMute = mute;
    if (m_bgMute) {
        pauseBackgroundMusic();
    }
    else if (m_bgMusicFile == NULL) {
        resumeBackgroundMusic();
    }
    else {
        playBackgroundMusic(m_bgMusicFile);
    }
}

void AudioManager::setSoundEffectMute(bool mute) {
    m_soundMute = mute;
    if (m_soundMute)
        stopAllEffects();
}

void AudioManager::preloadBackgroundMusic(const char* file) {
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(file);
}

void AudioManager::playBackgroundMusic(const char* file, bool loop) {
    if (m_bgMute)
        return;

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(file, loop);
}

void AudioManager::stopBackgroundMusic(bool releaseData) {
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(releaseData);
}

void AudioManager::pauseBackgroundMusic() {
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioManager::resumeBackgroundMusic() {
    if (m_bgMute)
        return;

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AudioManager::rewindBackgroundMusic() {
    SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

bool AudioManager::willPlayBackgroundMusic() {
    return SimpleAudioEngine::sharedEngine()->willPlayBackgroundMusic();
}

bool AudioManager::isBackgroundMusicPlaying() {
    return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

float AudioManager::getBackgroundMusicVolume() {
    return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void AudioManager::setBackgroundMusicVolume(float volume) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

void AudioManager::preloadEffect(const char* file) {
    SimpleAudioEngine::sharedEngine()->preloadEffect(file);
}

void AudioManager::unloadEffect(const char* file) {
    SimpleAudioEngine::sharedEngine()->unloadEffect(file);
}

unsigned int AudioManager::playEffect(const char* file, bool loop) {
    if (m_soundMute)
        return 0;

    return SimpleAudioEngine::sharedEngine()->playEffect(file, loop);
}

void AudioManager::pauseEffect(unsigned int soundId) {
    SimpleAudioEngine::sharedEngine()->pauseEffect(soundId);
}

void AudioManager::pauseAllEffects() {
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void AudioManager::resumeEffect(unsigned int soundId) {
    if (m_soundMute)
        return;

    SimpleAudioEngine::sharedEngine()->resumeEffect(soundId);
}

void AudioManager::resumeAllEffects() {
    if (m_soundMute)
        return;

    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void AudioManager::stopEffect(unsigned int soundId) {
    SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
}

void AudioManager::stopAllEffects() {
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

float AudioManager::getEffectsVolume() {
    return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}

void AudioManager::setEffectsVolume(float volume) {
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}
