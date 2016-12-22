#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
    int winingNumberIndex;
    struct CARD {
        int number1;
        int number2;
        int number3;
    } card;
    
    cocos2d::CCSprite* wheel;
    cocos2d::CCNode* numbersNode;
    
    // tried using CCArray of CCIntegers, but the casting from CCObjects was too cumbersome and CCInteger doesn't have an easy conversion to CCString. 
    int wheelArray[24] = {
        0,  2,  5,  4,  2,  3,
        0,  2,  5,  4,  8,  3,
        0,  2,  5,  3,  2,  3,
        0,  2,  5,  3, 10,  3
    };
    

    
    // a selector callback
    void getCard();
    
    void rotateWheelToWiningNumber();
    
    void getWiningNumber();
    
    void checkPosition();
    
    int getCurrentIndexFromWheelRotation();
    
    void checkIfNumberIsOnCard();
    
    void displayFinalLabel(bool won);
    
    // helper function to get the array index from the number
//    int getIndex(int number);
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void spinWheelCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
