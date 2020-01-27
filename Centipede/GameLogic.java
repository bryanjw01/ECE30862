import java.awt.*;
import java.util.*;
import java.math.*;


public class GameLogic extends Thread{
    
    public boolean syncReset;
    
    
    public boolean gameOverFlag;
    
   
    public int level;
    
    
    public int difficulty;
    
    
    public boolean paused;
    
    
    public int score;
    
    
    public Frame myFrame;
    public int arr_x[]=new int[20];
    public int arr_y[]=new int[20];
    public int size_arr=0;
    private GameSounds myGameSounds;
    private Centipede myCentipedes[];
    private Spider mySpider[];
    private Mushroom myMushrooms[][];
    private GameCanvas myGameCanvas;
    private Ship myShip;
    private HighScores myHighScores;    
    private Point myProjectiles[];
    private Random generator;
    
    
    public GameLogic(GameSounds inGameSounds, GameCanvas inGameCanvas, HighScores inHighScores, Mushroom inMushrooms[][], Centipede inCentipedes[], Ship inShip, Point inProjectiles[],Spider inSpider[]){
        myGameCanvas = inGameCanvas;
        myGameSounds = inGameSounds;
        myHighScores = inHighScores;
        myMushrooms = inMushrooms;
        myCentipedes = inCentipedes;
        myProjectiles = inProjectiles;
        myShip = inShip;
        mySpider=inSpider;

        generator = new Random();
        syncReset = false;
        difficulty = Settings.startDifficulty;
    }
    
    
    public void run(){
        int i;
        long lastCentUpdate = System.currentTimeMillis();
        long lastFireUpdate = System.currentTimeMillis();
        
        
        myGameCanvas.c.createBufferStrategy(2);
        
        
        while(true){
         
            if (syncReset == true){
                initGame();
                myGameSounds.newGame();
                syncReset = false;
                paused = false;
                myFrame.pauseGame.setText("Pause Game");
            }
            
           
            if (!paused){
               
                for (i = 0; i < myCentipedes.length; i++){
                    if ((myCentipedes[i] != null) &&
                        (myCentipedes[i].length != 0)){
                        break;
                    }
                }
                
                
                if (i == myCentipedes.length){
                    
                    myCentipedes[0] = new Centipede(Settings.centipedeStartSize, Settings.RIGHT, Settings.DOWN);
                    for (i = 0; i < Settings.centipedeStartSize; i++){
                        myCentipedes[0].segments[i] = new Point(- i * myCentipedes[0].horizontal, 0);
                    }
                    
                    
                    for (i = 1; i < Settings.centipedeStartSize; i++){
                        myCentipedes[i] = null;
                    }
                    
                    
                    myGameSounds.nextLevel();
                    level++;
                    score+=600;
                    Settings.centDelay = (int) Math.round(difficulty / Math.pow(Settings.levelFactor, level));
                }
                
               
                for (i = 0; i < mySpider.length; i++){
                    if ((mySpider[i] != null) &&
                        (mySpider[i].length != 0)){
                        break;
                    }
                }
                
                
                if (i == mySpider.length){
                    
                    mySpider[0] = new Spider(Settings.SpiderStartSize, Settings.RIGHT, Settings.DOWN);
                    for (i = 0; i < Settings.SpiderStartSize; i++){
                        mySpider[0].segments[i] = new Point(- i * mySpider[0].horizontal, 0);
                    }
                    
                    
                    for (i = 1; i < Settings.SpiderStartSize; i++){
                        mySpider[i] = null;
                    }
                    
                    
                    myGameSounds.nextLevel();
                    level++;
                    Settings.centDelay = (int) Math.round(difficulty / Math.pow(Settings.levelFactor, level));
                }
                if (System.currentTimeMillis() - lastCentUpdate > Settings.centDelay){
                    lastCentUpdate = System.currentTimeMillis();
                    moveCentipedes();
                    moveSpider();
                }
                
                
              
                if ((myShip.firing) && 
                    (System.currentTimeMillis() - lastFireUpdate > Settings.superLaserDelay)){
                    lastFireUpdate = System.currentTimeMillis();
                    myShip.fire();
                }
                
                
                moveProjectiles();
                
                
                if (!gameOverFlag){
                    moveShip();
                }
                
                
                if (myShip.invulnerableTime != 0){
                    myShip.invulnerableTime--;
                }
            }
            
            myGameCanvas.drawFrame();
        }
    }
    
   
    public void initGame(){
        int i, j, x, y;
        Settings.centDelay = difficulty;
        level = Settings.startLevel;
        myShip.lives = Settings.startLives;
        myShip.invulnerableTime = 0;
        score = 0;
        
        
        myCentipedes[0] = new Centipede(Settings.centipedeStartSize, Settings.RIGHT, Settings.DOWN);
        for (i = 0; i < Settings.centipedeStartSize; i++){
            myCentipedes[0].segments[i] = new Point(- i * myCentipedes[0].horizontal, 0);
        }
        
        
        for (i = 1; i < Settings.centipedeStartSize; i++){
            myCentipedes[i] = null;
        }
        mySpider[0] = new Spider(Settings.SpiderStartSize, Settings.RIGHT, Settings.DOWN);
        for (i = 0; i < Settings.SpiderStartSize; i++){
            mySpider[0].segments[i] = new Point(- i * mySpider[0].horizontal, 0);
        }
        
        
        for (i = 1; i < Settings.SpiderStartSize; i++){
            mySpider[i] = null;
        }
        
        for (i = 0; i < Settings.width; i++){
            for (j = 0; j < Settings.height; j++){
                myMushrooms[i][j] = null;
            }
        }
        
        
        for (i = 0; i < Settings.startShrooms; i++){
            do{
                x = (generator.nextInt(Settings.width-2))+1; 
                y = (generator.nextInt(Settings.height-3))+1; 
            }while(myMushrooms[x][y] != null);
            myMushrooms[x][y] = new Mushroom(new Point(x, y), Settings.shroomStartHealth);
        }
        
        
        for (i = 0; i < myProjectiles.length; i++){
            myProjectiles[i] = null;
        }
        
        
        gameOverFlag = false;
        myGameSounds.newGame();
    }
    
   
    private int overlap(Point loc){
        int result = 0;
        int i;
        Point scaledPoint;
        
        
        for (i = 0; i < myCentipedes.length; i++){
            if ((myCentipedes[i] != null) &&
                (myCentipedes[i].length != 0)){
                if (myCentipedes[i].contains(loc) != -1){
                    result += Settings.CENT;
                    break;
                }
            }
        }
        for (i = 0; i < mySpider.length; i++){
            if ((mySpider[i] != null) &&
                (mySpider[i].length != 0)){
                if (mySpider[i].contains(loc) != -1){
                    result += Settings.SPI;
                    break;
                }
            }
        }
       
        if (((loc.x < myMushrooms.length) && (loc.x >= 0)) &&
            ((loc.y < myMushrooms[loc.x].length) && (loc.y >= 0)) &&
            (myMushrooms[loc.x][loc.y] != null)){
            result += Settings.SHROOM;
        }
        
       
        scaledPoint = new Point((int) Math.floor(myShip.loc.x/Settings.scale), (int) Math.floor(myShip.loc.y/Settings.scale));
        if (loc.equals(scaledPoint)){
            result += Settings.SHIP;
        }
        
       
        for (i = 0; i < myProjectiles.length; i++){
            if (myProjectiles[i] != null){
                scaledPoint = new Point((int) Math.floor(myProjectiles[i].x/Settings.scale), (int) Math.floor(myProjectiles[i].y/Settings.scale));
                if (loc.equals(scaledPoint)){
                    result += Settings.PROJECTILE;
                    break;
                }
            }
        }
        
        
        if ((loc.x < 0) ||
            (loc.y < 0) ||
            (loc.x >= Settings.width) ||
            (loc.y >= Settings.height)){
            result += Settings.WALL;
        }
        
        return result;
    }
    
    
    private void moveSpider(){
        Point curHead;
        Point newHead;
        Point tempPoints[] = new Point[2];
        int overlapTest;
        
       
        for(int i = 0; i < mySpider.length; i++){    
           
        
            if (mySpider[i] != null){
                
                curHead = new Point(mySpider[i].segments[0].x, mySpider[i].segments[0].y);
                
               
                newHead = new Point(curHead.x + mySpider[i].horizontal, curHead.y+mySpider[i].vertical);
                
                
                overlapTest = overlap(newHead);
                
                
                if ((overlapTest%(Settings.SHIP*2) != Settings.SHIP) &&
                    (overlapTest%(Settings.PROJECTILE*2) != Settings.PROJECTILE) &&
                    (overlapTest != 0)){
                    
                    
                    if (curHead.y == 0){
                        mySpider[i].vertical = Settings.DOWN;
                    }else if (curHead.y == Settings.height - 1){
                        mySpider[i].vertical = Settings.UP;
                    }
                    
                    
                    newHead.x = curHead.x;
                    newHead.y = curHead.y + mySpider[i].vertical;
                    mySpider[i].horizontal *= -1;
                }
                
                
                tempPoints[1] = newHead;
                for (int j = 0; j < mySpider[i].length; j++){
                    tempPoints[j%2] = mySpider[i].segments[j];
                    mySpider[i].segments[j] = tempPoints[(j+1)%2];
                }
            }
        }
    }
    
    private void moveCentipedes(){
        Point curHead;
        Point newHead;
        Point tempPoints[] = new Point[2];
        int overlapTest;
        
        
        for(int i = 0; i < myCentipedes.length; i++){    
            
        
            if (myCentipedes[i] != null){
                
                curHead = new Point(myCentipedes[i].segments[0].x, myCentipedes[i].segments[0].y);
                
                
                newHead = new Point(curHead.x + myCentipedes[i].horizontal, curHead.y);
                
               
                overlapTest = overlap(newHead);
                
               
                if ((overlapTest%(Settings.SHIP*2) != Settings.SHIP) &&
                    (overlapTest%(Settings.PROJECTILE*2) != Settings.PROJECTILE) &&
                    (overlapTest != 0)){
                    
                    if (curHead.y == 0){
                        myCentipedes[i].vertical = Settings.DOWN;
                    }else if (curHead.y == Settings.height - 1){
                        myCentipedes[i].vertical = Settings.UP;
                    }
                    
                  
                    newHead.x = curHead.x;
                    newHead.y = curHead.y + myCentipedes[i].vertical;
                    myCentipedes[i].horizontal *= -1;
                }
                
                
                tempPoints[1] = newHead;
                for (int j = 0; j < myCentipedes[i].length; j++){
                    tempPoints[j%2] = myCentipedes[i].segments[j];
                    myCentipedes[i].segments[j] = tempPoints[(j+1)%2];
                }
            }
        }
    }
   
    private void moveShip(){
        int i, j;
        double distance, angle;
        double shipCenterX, shipCenterY;
        double testCenterX, testCenterY;
        int testX, testY;
        Point scaledDownPoint;
        
       
        shipCenterX = myShip.tryLoc.x + (Settings.scale/2.0);
        shipCenterY = myShip.tryLoc.y + (Settings.scale/2.0);
        
        
        for (i = 0; i < myCentipedes.length; i++){
            
            if (myCentipedes[i] != null){
            
                for (j = 0; j < myCentipedes[i].length; j++){
                    
                    testCenterX = Settings.scale*(myCentipedes[i].segments[j].x + 0.5);
                    testCenterY = Settings.scale*(myCentipedes[i].segments[j].y + 0.5);
                    
                    
                    distance = Math.sqrt(Math.pow(shipCenterX - testCenterX, 2) + Math.pow(shipCenterY - testCenterY, 2));
                                        
                   
                    if ((distance < Settings.scale) &&
                        (myShip.invulnerableTime == 0)){
                        
                        myGameSounds.shipExplode();
                        myShip.lives--;
                        myShip.invulnerableTime = Settings.invulnerableTime;
                        for(int x=0;x<size_arr;x++){
                            Point z=new Point(arr_x[x],arr_y[x]);
                            score+=10;
                            myMushrooms[arr_x[x]][arr_y[x]]=new Mushroom(z,Settings.shroomStartHealth);
                        }
                        size_arr=0;
                          
                        if (myShip.lives < 0){
                            gameOver();
                        }
                    }
                }
            }
            if(i<mySpider.length){
            if (mySpider[i] != null){
                
                for (j = 0; j < mySpider[i].length; j++){
                   
                    testCenterX = Settings.scale*(mySpider[i].segments[j].x + 0.5);
                    testCenterY = Settings.scale*(mySpider[i].segments[j].y + 0.5);
                    
                    
                    distance = Math.sqrt(Math.pow(shipCenterX - testCenterX, 2) + Math.pow(shipCenterY - testCenterY, 2));
                                        
                    
                    if ((distance < Settings.scale) &&
                        (myShip.invulnerableTime == 0)){
                        
                        myGameSounds.shipExplode();
                        myShip.lives--;
                        myShip.invulnerableTime = Settings.invulnerableTime;
                        for(int x=0;x<size_arr;x++){
                            Point y=new Point(arr_x[x],arr_y[x]);
                            score+=10;
                            myMushrooms[arr_x[x]][arr_y[x]]=new Mushroom(y,3);
                        }
                        size_arr=0;
                        
                        if (myShip.lives < 0){
                            gameOver();
                        }
                    }
                }}
            }
        }
        
      
        scaledDownPoint = new Point((int) Math.floor(shipCenterX/Settings.scale), (int) Math.floor(shipCenterY/Settings.scale));
        
      
        for (i = -1; i < 2; i++){
            for (j = -1; j < 2; j++){
                testX = scaledDownPoint.x + i;
                testY = scaledDownPoint.y + j;
                
                
                if (((testX < myMushrooms.length) && (testX >= 0)) &&
                    ((testY < myMushrooms[testX].length) && (testY >= 0)) &&
                    (myMushrooms[testX][testY] != null) &&
                    (myMushrooms[testX][testY].loc.y > (Settings.height - Settings.shipVerticalRange - 2))){
                    
                   
                    testCenterX = Settings.scale*(myMushrooms[testX][testY].loc.x + 0.5);
                    testCenterY = Settings.scale*(myMushrooms[testX][testY].loc.y + 0.5);
                    
                   
                    distance = Math.sqrt(Math.pow(shipCenterX - testCenterX, 2) + Math.pow(shipCenterY - testCenterY, 2));

                    
                    if (distance == 0){
                        shipCenterX = testCenterX + Settings.scale;
                        shipCenterY = testCenterY + Settings.scale;
                    }else if (distance < Settings.scale){
                        shipCenterX = testCenterX + Settings.scale*(shipCenterX - testCenterX)/distance;
                        shipCenterY = testCenterY + Settings.scale*(shipCenterY - testCenterY)/distance;
                    }
                }
            }
        }
        
      
        myShip.loc.x = (int) Math.round(shipCenterX - (Settings.scale/2.0));
        myShip.loc.y = (int) Math.round(shipCenterY - (Settings.scale/2.0));
    }
    
   
    private void moveProjectiles(){
        int overlapResult;
        int hitSegment;
        int newCentLength;
        int newCentVert;
        int newCentHor;
        Point scaledDownPoint;
        Point newCentHead;
        
        
        for (int i = 0; i < Settings.maxProjectiles; i++){
            
            
            if (myProjectiles[i] != null){
                
                
                scaledDownPoint = new Point((int) Math.round(myProjectiles[i].x/Settings.scale), (int) Math.floor(myProjectiles[i].y/Settings.scale));
                scaledDownPoint.y--;
                
                
                overlapResult = overlap(scaledDownPoint);
                
                
                if (overlapResult%(Settings.WALL*2) >= Settings.WALL){
                    myProjectiles[i] = null;
                    
                
                }else if (overlapResult%(Settings.CENT*2) >= Settings.CENT){
                    myProjectiles[i] = null;
                    
                    
                    for(int j = 0; j < Settings.centipedeStartSize; j++){
                        if(myCentipedes[j].health==2){
                            myCentipedes[j].health--;
                            score+=2;
                            break;
                        }
                        if ((myCentipedes[j] != null) &&
                            (myCentipedes[j].length != 0)){
                            hitSegment = myCentipedes[j].contains(scaledDownPoint);
                            
                           
                            if (hitSegment != -1){
                                
                               
                                if (hitSegment < myCentipedes[j].length - 1){
                                    
                                    
                                    for (int k = 0; k < myCentipedes.length; k++){
                                        
                                        
                                        if (myCentipedes[k] == null){
                                            
                                            newCentLength = myCentipedes[j].length - hitSegment - 1;
                                            newCentVert = myCentipedes[j].vertical;
                                            newCentHor = myCentipedes[j].horizontal;
                                            newCentHead = new Point(myCentipedes[j].segments[hitSegment+1].x, myCentipedes[j].segments[hitSegment+1].y);
                                            
                                            
                                            myCentipedes[k] = new Centipede(newCentLength, newCentHor, newCentVert);
                                            
                                            
                                            for (int m = 0; m < newCentLength; m++){
                                                myCentipedes[k].segments[m] = new Point(myCentipedes[j].segments[hitSegment+1+m].x, myCentipedes[j].segments[hitSegment+1+m].y);
                                            }
                                            
                                            
                                            break;
                                        }
                                    }
                                }
                                
                               
                                
                                score+=5;
                                

                                
                                myCentipedes[j].length = hitSegment;
                                myGameSounds.centDie();
                                break;
                            }
                        }
                    }
                    
                
                }else if (overlapResult%(Settings.SPI*2) >= Settings.SPI){
                    myProjectiles[i] = null;
                  
                    for(int j = 0; j < Settings.SpiderStartSize; j++){
                        if(mySpider[j].health==2){
                            mySpider[j].health--;
                            score+=100;
                            break;
                        }
                        score+=600;
                        
                        if ((mySpider[j] != null) &&
                            (mySpider[j].length != 0)){
                            hitSegment = mySpider[j].contains(scaledDownPoint);
                            
                           
                            if (hitSegment != -1){
                                
                               
                                if (hitSegment < mySpider[j].length - 1){
                                    
                                    
                                    for (int k = 0; k < mySpider.length; k++){
                                        
                                        
                                        if (mySpider[k] == null){
                                            
                                            newCentLength = mySpider[j].length - hitSegment - 1;
                                            newCentVert = mySpider[j].vertical;
                                            newCentHor = mySpider[j].horizontal;
                                            newCentHead = new Point(mySpider[j].segments[hitSegment+1].x, mySpider[j].segments[hitSegment+1].y);
                                            
                                            
                                            mySpider[k] = new Spider(newCentLength, newCentHor, newCentVert);
                                            
                                           
                                            for (int m = 0; m < newCentLength; m++){
                                                mySpider[k].segments[m] = new Point(mySpider[j].segments[hitSegment+1+m].x, mySpider[j].segments[hitSegment+1+m].y);
                                            }
                                            
                                           
                                            break;
                                        }
                                    }
                                }
                                
                                
                                mySpider[j].length = hitSegment;
                                myGameSounds.centDie();
                                break;
                            }
                        }
                    }
                    
                
                }
                else if (overlapResult%(Settings.SHROOM*2) >= Settings.SHROOM){
                    if (myMushrooms[scaledDownPoint.x][scaledDownPoint.y].health == 1){
                        arr_x[size_arr]=scaledDownPoint.x;
                        arr_y[size_arr]=scaledDownPoint.y;
                        size_arr++;
                        myMushrooms[scaledDownPoint.x][scaledDownPoint.y] = null;
                        score+=5;
                    }else{
                        myMushrooms[scaledDownPoint.x][scaledDownPoint.y].health--;
                        score+=1;
                    }
                    myGameSounds.shroomHit();
                    myProjectiles[i] = null;
                    
                
                }else{
                    myProjectiles[i].y--;
                }
            }
        }
    }
    
   
    public void gameOver(){
        gameOverFlag = true;
        myShip.firing = false;
        myGameSounds.gameOver();
        myHighScores.addHighScore(score);        
    }
}