/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Level.cpp
 * $Id: Level.cpp v 1.0 2013-12-26 10:11:14 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:06:51 $
 * @brief
 *
 ******************************************************************/

#include "Level.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define PASS_RATE       0.6
#define TWO_STAR_RATE   0.8
#define FULL_STAR_RATE  0.99
Level::Level(int level, int seasonId) {
    m_level = level;
    m_seasonId = seasonId;
    m_locked = true;
    m_passCountRecord = 0;
    resetProgress();
}

Level::~Level() {
}

void Level::clearQuestions() {
    m_questions.clear();
}

void Level::addQuestion(Question q) {
    q.id = m_questions.size()+1;
    m_questions.push_back(q);
}

void Level::resetProgress() {
    m_passCount = 0;
    m_failCount = 0;
    m_progress = 0;
}

void Level::resetRecord() {
    m_passCountRecord = 0;
    m_locked = true;
}

void Level::initRecord(const LevelRecord& record) {
    if (record.level != m_level)
        return;

    m_passCountRecord = record.passCount;
    m_locked = record.locked;
}

LevelRecord Level::record() const {
    LevelRecord lr;
    lr.level = m_level;
    lr.locked = m_locked;
    lr.passCount = m_passCountRecord;
    return lr;
}

bool Level::fail() const {
    return m_failCount >= questionCount() * (1 - PASS_RATE);
}

void Level::passCurrentQuestion() {
    m_passCount++;
    Record::instance()->incTotalPass();
    if (m_passCount > m_passCountRecord)
        m_passCountRecord = m_passCount;
}

void Level::failCurrentQuestion() {
    m_failCount++;
    Record::instance()->incTotalFail();
}

Question Level::nextQuestion() {
    if (currentProgress() >= questionCount())
        return Question();

    return m_questions[m_progress++];
}

Question Level::prevQuestion() {
    if (currentProgress() < 0)
        return Question();

    return m_questions[m_progress--];
}

void Level::shuffleQuestion() {
    srandom(time(NULL));
    int count = questionCount();
    for (int i = 0; i < count; i++) {
        int pos = random() % count;
        if (pos != i)
            swap(m_questions[i], m_questions[pos]);
    }
    for (int i = 0; i < count; i++) {
        m_questions[i].id = i+1;
    }
}

int Level::evaluateStars(int passCount) const {
    int count = questionCount();
    if (count <= 0)
        return 0;

    float passRate = passCount*1.0f/count;
    if (passRate >= FULL_STAR_RATE) {
        return 3;
    }
    else if (passRate >= TWO_STAR_RATE) {
        return 2;
    }
    else if (passRate >= PASS_RATE) {
        return 1;
    }

    return 0;
}

bool Level::pass(int passCount) const {
    return passCount >= questionCount() * PASS_RATE;
}

