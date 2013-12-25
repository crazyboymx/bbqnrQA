/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: OptionLayer.h
 * $Id: OptionLayer.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:47:52 $
 * @brief
 *
 ******************************************************************/

#ifndef __OPTIONLAYER_H_
#define __OPTIONLAYER_H_

#include <cocos2d.h>
#include "Question.h"

USING_NS_CC;

class OptionLayer: public CCLayerColor {
public:
    OptionLayer();
    virtual ~OptionLayer();
    CREATE_FUNC(OptionLayer);
    virtual bool init();

    void setOption(const char* option, bool isAnswer);

private:
    const char     *m_option;
    bool            m_isAnswer;
    CCLabelBMFont  *m_optionLabel;
    CCSprite       *m_bgSprite;
};

#endif // __OPTIONLAYER_H_
