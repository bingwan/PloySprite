

#ifndef CCWater_CCDrawLineLayer_h
#define CCWater_CCDrawLineLayer_h

#include "cocos2d.h"

USING_NS_CC;


class BWDrawLayer : public LayerColor
{
public:
    BWDrawLayer();
    virtual ~BWDrawLayer();
	virtual bool init();  
    
    virtual void draw() override;
    static BWDrawLayer * create(const Color4B& color, GLfloat width, GLfloat height);

    
    void setDrawPos(std::vector<Point>* pVPos ){_vDrawPos = *pVPos;}
private:
    std::vector<Point> _vDrawPos;

};


#endif
