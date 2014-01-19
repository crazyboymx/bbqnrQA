/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: AudioManager.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:12:13 $
 * @brief
 *
 ******************************************************************/

#ifndef AudioManager_H_
#define AudioManager_H_

class AudioManager {
public:
    static AudioManager* instance();
    virtual ~AudioManager() { }

    bool isBackgroundMute() { return m_bgMute; }
    bool isSoundMute() { return m_soundMute; }
    void setBackgroundMusic(const char* file) { m_bgMusicFile = file; }
    void setBackgroundMute(bool mute);
    void setSoundEffectMute(bool mute);

    void preloadBackgroundMusic(const char* file);
    void playBackgroundMusic(const char* file = 0, bool loop = true);
    void stopBackgroundMusic(bool releaseData = false);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    void rewindBackgroundMusic();
    bool willPlayBackgroundMusic();
    bool isBackgroundMusicPlaying();
    float getBackgroundMusicVolume();
    void setBackgroundMusicVolume(float volume);

    void preloadEffect(const char* file);
    void unloadEffect(const char* file);
    unsigned int playEffect(const char* file, bool loop = false);
    void pauseEffect(unsigned int soundId);
    void pauseAllEffects();
    void resumeEffect(unsigned int soundId);
    void resumeAllEffects();
    void stopEffect(unsigned int soundId);
    void stopAllEffects();
    float getEffectsVolume();
    void setEffectsVolume(float volume);
protected:
    AudioManager() : m_bgMute(false), m_soundMute(false), m_bgMusicFile(0) { }
    AudioManager(const AudioManager&) { }
private:
    bool m_bgMute;
    bool m_soundMute;
    const char* m_bgMusicFile;

    static AudioManager* g_instance;
};

#endif /* AudioManager_H_ */
