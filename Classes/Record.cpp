/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Record.cpp
 * $Id: Record.cpp v 1.0 2013-12-26 14:33:02 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 19:53:55 $
 * @brief
 *
 ******************************************************************/

#include "Record.h"
#include <cocos2d.h>
#include <cstdio>

//USING_NS_CC;

string dbPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "save.db";

void Record::load() {
    cocos2d::CCLog("dbPath: %s", dbPath.c_str());
    FILE* fp = fopen(dbPath.c_str(), "rb");
    if (fp == NULL)
        return;

    fread(this, sizeof(Record), 1, fp);
    fclose(fp);
}

void Record::save() {
    cocos2d::CCLog("dbPath: %s", dbPath.c_str());
    FILE* fp = fopen(dbPath.c_str(), "wb");
    if (fp == NULL)
        return;

    fwrite(this, sizeof(Record), 1, fp);
    fclose(fp);
}

void Record::setSeasonRecord(const SeasonRecord& record) {
    m_record[record.seasonId] = record;
}

