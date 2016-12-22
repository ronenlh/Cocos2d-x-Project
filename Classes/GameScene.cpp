#include "GameScene.h"
#include "Definitions.h"
#include "AppMacros.h"
#include <sstream>

USING_NS_CC;
using namespace std;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // add a "spin" icon to spin the wheel. it's an autorelease object
    CCMenuItemImage *pSpinButton = CCMenuItemImage::create(
                                        "button.png",
                                        "buttonRed.png",
                                        this,
                                        menu_selector(GameScene::spinWheelCallback));
    pSpinButton->setScale(0.5);
	pSpinButton->setPosition(ccp(origin.x + visibleSize.width - pSpinButton->getContentSize().width/2 ,
                                origin.y + pSpinButton->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pSpinButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 3);

    
    //add wheel
    wheel = CCSprite::create("fortune_aces.png");
    wheel->setPosition(CCPoint(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y ));
    wheel->setScale(1);
    this->addChild(wheel, 1);
    
    // add a label shows "Spin The Wheel"
    CCLabelTTF* title = CCLabelTTF::create("Spin The Wheel", "Helvetica", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    title->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    title->enableShadow(CCSize(1.5, 1.5), 1.5, 1.5);
    
    this->addChild(title, 5);

    // add casino splash screen"
    CCSprite* casinoBackground = CCSprite::create("casino.jpg");

    // position the sprite on the center of the screen
    casinoBackground->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(casinoBackground, 0);
    
    
    // this node includes the instructions and the three numbers
    numbersNode = CCNode::create();
    numbersNode->setPosition(ccp(origin.x + 3*(visibleSize.width/4),
                                 origin.y + visibleSize.height/2));
    this->addChild(numbersNode, 2);
    
    // add card to the node
    CCSprite* card = CCSprite::create("card.png");
    card->setPosition(ccp(origin.x + 3*(visibleSize.width/4),
                                 origin.y + visibleSize.height/2));
    this->addChild(card, 1);
    
    // a label with instructions on the card
    CCLabelTTF* instructions = CCLabelTTF::create("Click \n to \n Spin!", "Helvetica", 23);
    instructions->setFontFillColor(ccRED);
    numbersNode->addChild(instructions, 1);
    
    // another label with instructions on the card
    CCLabelTTF* instructions2 = CCLabelTTF::create("Match any number \n with the wheel", "Helvetica", 9);
    instructions2->setFontFillColor(ccBLACK);
    instructions2->setPositionY(65);
    numbersNode->addChild(instructions2, 1);
    
    return true;
}


void GameScene::spinWheelCallback(CCObject* pSender)
{
    // remove previous numbers
    numbersNode->removeAllChildrenWithCleanup(false);
    
    // remove final label from scene
    this->removeChildByTag(FINAL_LABEL_TAG);
    
    getCard();
    
    auto rotateOnce = CCRotateBy::create(3, 360*2);
    wheel->runAction(rotateOnce);
    CCLOG("wheel rotated once");
    
    // get a random number after 3 secs and spin the wheel there
    this->scheduleOnce(schedule_selector(GameScene::getWiningNumber), 3);
}

void GameScene::getCard() {
    
    // randomize card numbers from the array
    card.number1 = wheelArray[rand() % 24];
    card.number2 = wheelArray[rand() % 24];
    card.number3 = wheelArray[rand() % 24];

    // tried to make a CCArray of the three labels and iterate with the CCARRAY_FOREACH
    // but referencing each label inside the foreach macro became hard to read.
    // I should check screen size for the font size and positioning
    CCLabelTTF* pLabel1 = CCLabelTTF::create("", "Helvetica", 32);
    CCLabelTTF* pLabel2 = CCLabelTTF::create("", "Helvetica", 32);
    CCLabelTTF* pLabel3 = CCLabelTTF::create("", "Helvetica", 32);
    
    // setting for color black
    pLabel1->setFontFillColor(ccBLACK);
    pLabel2->setFontFillColor(ccBLACK);
    pLabel3->setFontFillColor(ccBLACK);
    
    // set positioning
    pLabel1->setPositionY(40);
    pLabel3->setPositionY(-40);
    
    
    // create a stringstream for the three labels
    // I used a stringstream since I don't know how to cast a int into string
    // didn't manage to use CCString yet, not enough methods
    stringstream ss(stringstream::in | stringstream::out);
    string s;
    
    if (card.number1 == 0)  ss << "A";
    else                    ss << card.number1;
    s = ss.str();
    pLabel1->setString(s.c_str());
    CCLOG("1st number changed %s", s.c_str());
    
    
    ss.str(""); // clearing the stringstream
    if (card.number2 == 0)  ss << "A";
    else                    ss << card.number2;
    s = ss.str();
    pLabel2->setString(s.c_str());
    CCLOG("2nd number changed %s", s.c_str());
    
    
    ss.str(""); // clearing the stringstream
    if (card.number3 == 0)  ss << "A";
    else                    ss << card.number3;
    s = ss.str();
    pLabel3->setString(s.c_str());
    CCLOG("3rd number changed %s", s.c_str());
    
    // add the labels as childs to the numbers node
    numbersNode->addChild(pLabel1, 1);
    numbersNode->addChild(pLabel2, 1);
    numbersNode->addChild(pLabel3, 1);
}

void GameScene::getWiningNumber(){
    // get a random numbers
    // command the wheel to turn to that number
    
    winingNumberIndex = rand() % 24;
    CCLOG("wining index is %d, corresponds to number %d", winingNumberIndex, wheelArray[winingNumberIndex]);

    rotateWheelToWiningNumber();
    CCLOG("stopping wheel at %d", wheelArray[winingNumberIndex]);
}

void GameScene::rotateWheelToWiningNumber() {
    // define the action, every 15 degrees is a different number in the wheel, each moves in 0.5 secs
    auto rotate15D = CCRotateBy::create(0.5, 15);
    auto checkCallback = CCCallFunc::create(this, callfunc_selector(GameScene::checkPosition));
    auto seq = CCSequence::create(rotate15D, checkCallback, NULL);
    
    // repeat forever the sequence, in which it turns 15degs and checks if the number is the chosen one
    wheel->runAction(CCRepeatForever::create(seq));
}

void GameScene::checkPosition() {
    int i = getCurrentIndexFromWheelRotation();
    CCLog("current number is %d", wheelArray[i]);

    if (i == winingNumberIndex) {
        wheel->stopAllActions();
        // TODO: implement an ease-out animation
        
        checkIfNumberIsOnCard();
    }
}

int GameScene::getCurrentIndexFromWheelRotation(){
    // here's the math:
    // - modulo to ignore the number of complete rotations
    // - division by 15 the wheel rotates 15deg for each number, there are no in-betweens
    return (((int) wheel->getRotation() % 360) / 15);
}

void GameScene::checkIfNumberIsOnCard(){
    // check if number is on the card
    if (wheelArray[winingNumberIndex] == card.number1
        || wheelArray[winingNumberIndex] == card.number2
        || wheelArray[winingNumberIndex] == card.number2) {
        CCLog("WON!");
        displayFinalLabel(true);
    } else {
        CCLog("Too bad, try again!");
        displayFinalLabel(false);
    }
}

void GameScene::displayFinalLabel(bool won){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // TODO: make this static so it doesn't get instatiated every time
    CCLabelTTF* finalLabel = CCLabelTTF::create("", "Helvetica", 40);
    finalLabel->setFontFillColor(ccRED);
    finalLabel->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    finalLabel->setTag(FINAL_LABEL_TAG);
    finalLabel->enableShadow(CCSize(1.5, 1.5), 1.5, 1.5);
    
    if (won) {
        finalLabel->setString("YOU WON!");
        finalLabel->setFontSize(50);
    } else {
        finalLabel->setString("Too bad, try again!");
    }
    
    this->addChild(finalLabel, 5);
}

