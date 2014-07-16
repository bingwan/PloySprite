

#include "BWDrawLayer.h"

BWDrawLayer::BWDrawLayer()
{}

BWDrawLayer::~BWDrawLayer()
{}

BWDrawLayer * BWDrawLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
    BWDrawLayer * pLayer = new BWDrawLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool BWDrawLayer::init()
{
	if ( !LayerColor::init() )
	{
		return false;
	}
    return true;
}

void BWDrawLayer::draw()
{
    ccDrawColor4B(0,255,0,255);
    const int nNum = _vDrawPos.size();
    Point * PosArray = new Point[nNum];
    
    for(int i=0;i<nNum;++i)
    {
        PosArray[i] = _vDrawPos[i];
    }
    ccDrawSolidPoly(PosArray, nNum, Color4F(0,0,0,255) );
}

//取多变行精灵
Sprite* UIManager::getPloySprite(std::vector<Point>* pVDrawPos,const char* pszPngName )
{
    
    Sprite* pSpriteWH = Sprite::create(pszPngName);
    Size contentSize = pSpriteWH->getContentSize();
    
    BWDrawLayer* pTestLayer = BWDrawLayer::create(Color4B(0,0,0,255), contentSize.width, contentSize.height);
    pTestLayer->setDrawPos(pVDrawPos);
    
    //========================================
    RenderTexture* pRenderTexture2 = RenderTexture::create(contentSize.width, contentSize.height);
    pRenderTexture2->begin();
    //========================================
    pTestLayer->setAnchorPoint(Point(0,0));
    pTestLayer->setPosition(Point(contentSize.width*0.5,contentSize.height*0.5));
    pTestLayer->setColor(Color3B::BLACK);
    BlendFunc oldBlendFunc2 = pTestLayer->getBlendFunc();
    pTestLayer->setBlendFunc((BlendFunc){GL_ZERO,GL_SRC_ALPHA});// 从底图切出  上层图形
    pTestLayer->visit();
    pTestLayer->setBlendFunc(oldBlendFunc2);
    //========================================
    
    pRenderTexture2->end();
    
    Texture2D* pNewTexture = pRenderTexture2->getSprite()->getTexture();
    Sprite* pNewSprite = Sprite::createWithTexture(pNewTexture);
    //========================================
    //========================================
    //========================================
    //========================================
    //========================================
    RenderTexture* pRenderTexture3 = RenderTexture::create(contentSize.width, contentSize.height);
    pRenderTexture3->begin();
    //========================================
    Sprite* pBgDrawSprite = Sprite::create(pszPngName);
    pBgDrawSprite->setAnchorPoint(Point(0,0));
    pBgDrawSprite->setPosition(Point(0,0));
    pBgDrawSprite->setFlippedY(true);
    pBgDrawSprite->visit();
    pBgDrawSprite->setFlippedY(false);
    //========================================
    //========================================
    pNewSprite->setAnchorPoint(Point(0,0));
    pNewSprite->setPosition(Point(0,0));
    BlendFunc oldBlendFunc3 = pNewSprite->getBlendFunc();
    pNewSprite->setBlendFunc((BlendFunc){GL_ZERO,GL_SRC_ALPHA});// 从底图切出  上层图形
    pNewSprite->setFlippedY(true);
    pNewSprite->visit();
    pNewSprite->setFlippedY(false);
    pNewSprite->setBlendFunc(oldBlendFunc3);
    //========================================
    pRenderTexture3->end();
    
    Texture2D* pNewTexture3 = pRenderTexture3->getSprite()->getTexture();
    Sprite* pNewSprite3 = Sprite::createWithTexture(pNewTexture3);
    
    return pNewSprite3;
}



