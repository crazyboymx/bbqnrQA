/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LevelNode.h
 * $Id: LevelNode.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:20:46 $
 * @brief
 *
 ******************************************************************/

#ifndef __LEVELNODE_H_
#define __LEVELNODE_H_

#include <cocos2d.h>
#include "Level.h"

USING_NS_CC;
using namespace std;

class LevelNode : public CCNode {
public:
    LevelNode();
    virtual ~LevelNode();
    CREATE_FUNC(LevelNode);
    virtual bool init();

    void initWithLevel(Level* level);
    Level* level() const { return m_level; }
private:
    Level*          m_level;
    CCLabelTTF*     m_levelLabel;
    CCSprite*       m_levelSprite;
};

#endif // __LEVELNODE_H_
