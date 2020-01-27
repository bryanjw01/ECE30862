import java.awt.*;
import javax.swing.*;


public class Centipede_Project extends JApplet{
    private static final long serialVersionUID = 1L;

    
    private GameSounds myGameSounds;
    
   
    private HighScores myHighScores;
    
   
    private GameCanvas myGameCanvas;
    
    
    private GameLogic myGameLogic;
    
    
    private Frame myFrame;
    
   
    private Mushroom myMushrooms[][];
    
   
    private Centipede myCentipedes[];

    private Spider mySpider[];
    
   
    private Ship myShip;
    
    
    private Point myProjectiles[];
    
  
    public static void main(String[] args){
        new Centipede_Project();
    }
    
    public Centipede_Project(){
       
        myGameSounds = new GameSounds();
        myHighScores = new HighScores();
        myMushrooms = new Mushroom[Settings.width][Settings.height];
        myProjectiles = new Point[Settings.maxProjectiles];        
        myShip = new Ship(myGameSounds, myProjectiles);
        myCentipedes = new Centipede[Settings.centipedeStartSize];
        mySpider=new Spider[Settings.SpiderStartSize];        
        myGameCanvas = new GameCanvas(myGameSounds, myMushrooms, myCentipedes, myShip, myProjectiles,mySpider);
        myGameLogic = new GameLogic(myGameSounds, myGameCanvas, myHighScores, myMushrooms, myCentipedes, myShip, myProjectiles,mySpider);
        myFrame = new Frame(myGameLogic, myGameCanvas, myHighScores);
        
        myGameCanvas.myGameLogic = myGameLogic;
        myHighScores.myFrame = myFrame;
        myGameLogic.myFrame = myFrame;
        myGameLogic.syncReset = true;
        
        myGameLogic.start();
        try{
            myGameLogic.join();
        }catch(Exception e){}
    }
}