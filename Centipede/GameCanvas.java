import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.File;
import javax.sound.sampled.*;

public class GameCanvas implements MouseListener, MouseMotionListener{
   
    public Canvas c;
    
    
    public GameLogic myGameLogic;
    
    
    private Mushroom myMushrooms[][];
    
   
    private Centipede myCentipedes[];

    private Spider mySpider[];
    
    
    private Point myProjectiles[];
    
    
    private GameSounds myGameSounds;
    
    
    private Ship myShip;
    
   
    private BufferedImage cursorImg;
    
    
    private Cursor blankCursor;

    
    
   
    public GameCanvas (GameSounds inGameSounds, Mushroom inMushrooms[][], Centipede inCentipedes[], Ship inShip, Point inProjectiles[],Spider inSpider[]){
        myGameSounds = inGameSounds;
        myMushrooms = inMushrooms;
        myCentipedes = inCentipedes;
        myShip = inShip;
        myProjectiles = inProjectiles;
        mySpider=inSpider;
       
        cursorImg = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);
        
       
        blankCursor = Toolkit.getDefaultToolkit().createCustomCursor(cursorImg, new Point(0, 0), "blank cursor");
        
        
        c = new Canvas();
        c.setSize(Settings.width*Settings.scale, (Settings.height+2)*Settings.scale);
        c.setVisible(true);
        
        
        c.addMouseListener(this);
        c.addMouseMotionListener(this);
    }
    
    
    public void drawFrame() {
        
        BufferStrategy bf = c.getBufferStrategy();
        Graphics g = null;
        
        try {
            g = bf.getDrawGraphics();
            g.setColor(Color.BLACK);
            
            
            g.fillRect(0, 0, Settings.width*Settings.scale, (Settings.height+2)*Settings.scale);
            
            if (myProjectiles != null){
                DrawGraphics.drawProjectiles(g, myProjectiles);
            }
            
            if (myMushrooms != null){
                DrawGraphics.drawMushrooms(g, myMushrooms);   
            }
            
            if (myCentipedes != null){
                DrawGraphics.drawCentipedes(g, myCentipedes);
            }
            
            if(mySpider != null){
                DrawGraphics.drawSpider(g,mySpider);
            }

            if (myGameLogic != null && myShip != null){
                DrawGraphics.drawText(g, myShip, myGameLogic);
            }
            
            
            if (!myGameLogic.gameOverFlag || (myShip.invulnerableTime != 0)){
                if (myShip != null){
                    DrawGraphics.drawShip(g, myShip);
                }
            }
            
       
        }finally{
            g.dispose();
        }
        
        
        bf.show();
        
       
        Toolkit.getDefaultToolkit().sync();
    }
    
    
    public void mouseClicked(MouseEvent e){
    }
    
   
    public void mouseEntered(MouseEvent e){
    }
    
    
    public void mouseExited(MouseEvent e){
    }
    
    
    public void mousePressed(MouseEvent e)
    {
        
        if (!myGameLogic.paused)
        {
            
            
            if (myGameLogic.gameOverFlag){
                myShip.firing = false;
                
            
            }else if (Settings.superLaser){
                myShip.firing = true;
                
            
            }else{
                myShip.firing = false;
                myShip.fire();

                Runnable thrd=new Runnable(){
                    
                    @Override
                    public void run(){
                        try{
                            AudioInputStream laser=AudioSystem.getAudioInputStream(new File("laser.wav"));
                            Clip sound=AudioSystem.getClip();
                            sound.open(laser);
                            sound.start();
                            Thread.sleep(1000);
                        }catch(Exception e){}
                    }
                };
                new Thread(thrd).start();
            }
        }
    }
    
    
    public void mouseReleased(MouseEvent e){
        if (!myGameLogic.paused){
            myShip.firing = false;
        }
    }
    

    public void mouseMoved(MouseEvent e){
        int tryX = e.getX();
        int tryY = e.getY();
        Cursor nextCursor = blankCursor;
        
        
        if ((!myGameLogic.paused) && (!myGameLogic.gameOverFlag)){
            
            
            if (tryX < 0){
                myShip.tryLoc.x = 0;
                nextCursor = Cursor.getDefaultCursor();
            }else if (tryX > (Settings.width - 1)*Settings.scale){
                myShip.tryLoc.x = (Settings.width - 1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else{
                myShip.tryLoc.x = tryX;
            }
            
            if (tryY < (Settings.height-Settings.shipVerticalRange-1)*Settings.scale){
                myShip.tryLoc.y = (Settings.height-Settings.shipVerticalRange-1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else if (tryY > (Settings.height-1)*Settings.scale){
                myShip.tryLoc.y = (Settings.height-1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else{
                myShip.tryLoc.y = tryY;
            }
            
           
        }else{
            nextCursor = Cursor.getDefaultCursor();
        }
        
        
        c.setCursor(nextCursor);
    }
    
    
    public void mouseDragged(MouseEvent e){    
        int tryX = e.getX();
        int tryY = e.getY();
        Cursor nextCursor = blankCursor;
        
        
        if ((!myGameLogic.paused) && (!myGameLogic.gameOverFlag)){
            
           
            if (tryX < 0){
                myShip.tryLoc.x = 0;
                nextCursor = Cursor.getDefaultCursor();
            }else if (tryX > (Settings.width - 1)*Settings.scale){
                myShip.tryLoc.x = (Settings.width - 1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else{
                myShip.tryLoc.x = tryX;
            }
            
            if (tryY < (Settings.height-Settings.shipVerticalRange-1)*Settings.scale){
                myShip.tryLoc.y = (Settings.height-Settings.shipVerticalRange-1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else if (tryY > (Settings.height-1)*Settings.scale){
                myShip.tryLoc.y = (Settings.height-1)*Settings.scale;
                nextCursor = Cursor.getDefaultCursor();
            }else{
                myShip.tryLoc.y = tryY;
            }
            
          
        }else{
            nextCursor = Cursor.getDefaultCursor();
        }
        
        
        c.setCursor(nextCursor);
    }
}