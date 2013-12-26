/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Level.h
 * $Id: Level.h v 1.0 2013-12-26 09:06:51 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 17:16:08 $
 * @brief
 *
 ******************************************************************/

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <string>
#include <vector>
#include "Question.h"
#include "Record.h"

using namespace std;

class Level {
public:
    Level(int level);
    virtual ~Level();

    void clearQuestions();
    void addQuestion(Question q);

    void resetProgress();
    void resetRecord();
    void initRecord(const LevelRecord& record);
    LevelRecord record() const;

    int level() const { return m_level; }
    int currentProgress() const { return m_progress; }
    int passCount() const { return m_passCount; }
    int failCount() const { return m_failCount; }
    int passCountRecord() const { return m_passCountRecord; }
    int starCount() const { return evaluateStars(m_passCount); }
    int starCountRecord() const { return evaluateStars(m_passCountRecord); }
    int questionCount() const { return m_questions.size(); }
    bool finish() const { return !fail() && currentProgress() < questionCount(); }
    bool pass() const { return !fail() && pass(m_passCount); }
    bool hasPassedOnce() const { return pass(m_passCountRecord); }
    bool fail() const;
    bool locked() const { return m_locked; }

    void passCurrentQuestion();
    void failCurrentQuestion();
    void unlock() { m_locked = false; }
    void lock() { m_locked = true; }
    Question nextQuesion();
    Question prevQuesion();
    void shuffleQuestion();

private:
    int evaluateStars(int passCount) const;
    bool pass(int passCount) const;

private:
    int m_level;
    int m_locked;

    int m_passCount;
    int m_failCount;
    int m_progress;

    int m_passCountRecord;

    vector<Question> m_questions;
};

#endif //__LEVEL_H__
