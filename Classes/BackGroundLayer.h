/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Question.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:12:13 $
 * @brief
 *
 ******************************************************************/

#ifndef BACKGROUNDLAYER_H_
#define BACKGROUNDLAYER_H_

#include <cocos2d.h>

class BackGroundLayer: public cocos2d::CCLayerColor {
public:
    BackGroundLayer();
    virtual ~BackGroundLayer();
    CREATE_FUNC(BackGroundLayer);
    virtual bool init();

private:
};

#endif /* BACKGROUNDLAYER_H_ */
