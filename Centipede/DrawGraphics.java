import java.awt.*;
import java.util.*;


public class DrawGraphics{
    
    private static Random generator = new Random();
    
    
    public static void drawText(Graphics g, Ship myShip, GameLogic myGameLogic){
        String livesString = "Lives: " + myShip.lives;
        String scoreString = "Score: " + myGameLogic.score;
        
        g.setColor(Color.WHITE);
        g.setFont(new Font("SansSerif", Font.BOLD, Settings.scale));
        
        
        g.drawString(scoreString, Settings.scale, (Settings.height+1)*Settings.scale);
       
        g.drawString(livesString, Settings.scale*(Settings.width - livesString.length()/2 - 1), (Settings.height+1)*Settings.scale);
    }
    
   
    public static void drawMushrooms(Graphics g, Mushroom myMushrooms[][]){
        int startAngle, arcAngle;
        
       
        for (int i = 0; i < myMushrooms.length; i++){
            
            
            for (int j = 0; j < myMushrooms[i].length; j++){
                
                
                if (myMushrooms[i][j] != null){
                    
                   
                    g.setColor(Color.GRAY);
                    g.fillRect((int) Math.round((myMushrooms[i][j].loc.x + 0.3)*Settings.scale), (int) Math.floor((myMushrooms[i][j].loc.y + 0.5)*Settings.scale), (int) Math.floor(Settings.scale*0.4), (int) Math.floor(Settings.scale*0.5));
                    
                    
                    g.setColor(Color.RED);
                    g.fillArc(myMushrooms[i][j].loc.x*Settings.scale, myMushrooms[i][j].loc.y*Settings.scale, Settings.scale, Settings.scale, 0, 180);
                    
                    
                    g.setColor(Color.YELLOW);
                    g.fillOval((int) Math.round((myMushrooms[i][j].loc.x + 0.1)*Settings.scale), (int) Math.round((myMushrooms[i][j].loc.y + 0.2)*Settings.scale), Settings.scale/5, Settings.scale/5);
                    g.fillOval((int) Math.round((myMushrooms[i][j].loc.x + 0.4)*Settings.scale), (int) Math.round((myMushrooms[i][j].loc.y + 0.1)*Settings.scale), Settings.scale/5, Settings.scale/5);
                    g.fillOval((int) Math.round((myMushrooms[i][j].loc.x + 0.7)*Settings.scale), (int) Math.round((myMushrooms[i][j].loc.y + 0.2)*Settings.scale), Settings.scale/5, Settings.scale/5);
                    
                   
                    g.setColor(Color.BLACK);
                    switch (myMushrooms[i][j].health){
                        case 1:
                            g.fillArc(myMushrooms[i][j].loc.x*Settings.scale, (int) Math.round((myMushrooms[i][j].loc.y + 0.2)*Settings.scale), Settings.scale, Settings.scale, 45, -270);
                            break;
                        case 2:
                            g.fillArc(myMushrooms[i][j].loc.x*Settings.scale, (int) Math.round((myMushrooms[i][j].loc.y + 0.2)*Settings.scale), Settings.scale, Settings.scale, -45, -90);
                            break;
                    }
                }
            }
        }
    }
    
    
    public static void drawCentipedes(Graphics g, Centipede myCentipedes[]){
        int i, j;
        
       
        Color head = new Color(255*Settings.centDelay/Settings.centDelayEasy, 255, 255*(1 - Settings.centDelay/Settings.centDelayEasy));
        Color body = new Color(255*Settings.centDelay/Settings.centDelayEasy, 0, 255*(1 - Settings.centDelay/Settings.centDelayEasy));
        
       
        for(i = 0; i < myCentipedes.length; i++){
            
            if ((myCentipedes[i] != null) &&
                (myCentipedes[i].length != 0)){
                
                g.setColor(head);
                g.fillOval(myCentipedes[i].segments[0].x*Settings.scale, myCentipedes[i].segments[0].y*Settings.scale, Settings.scale, Settings.scale);
                
                
                g.setColor(body);
                for (j = 1; j < myCentipedes[i].length; j++){
                    g.fillOval(myCentipedes[i].segments[j].x*Settings.scale, myCentipedes[i].segments[j].y*Settings.scale, Settings.scale, Settings.scale);
                }
            }
        }
    }
   
    public static void drawSpider(Graphics g, Spider mySpider[]){
        int i, j;
        
        
        Color head = new Color(255*Settings.centDelay/Settings.centDelayEasy, 255, 255*(1 - Settings.centDelay/Settings.centDelayEasy));
        Color body = new Color(255*Settings.centDelay/Settings.centDelayEasy, 0, 255*(1 - Settings.centDelay/Settings.centDelayEasy));
        
        
        for(i = 0; i < mySpider.length; i++){
           
            if ((mySpider[i] != null) &&
                (mySpider[i].length != 0)){
               
                g.setColor(head);
                g.fillOval(mySpider[i].segments[0].x*Settings.scale, mySpider[i].segments[0].y*Settings.scale, Settings.scale, Settings.scale);
                
                
                g.setColor(body);
                for (j = 1; j < mySpider[i].length; j++){
                    g.fillOval(mySpider[i].segments[j].x*Settings.scale, mySpider[i].segments[j].y*Settings.scale, Settings.scale, Settings.scale);
                }
            }
        }
    }
    
    
    public static void drawShip(Graphics g, Ship myShip){
        int i;
        
        
        if (myShip.invulnerableTime == 0){
            
           
            g.setColor(Color.GREEN);
            int[] xPoints = {myShip.loc.x,myShip.loc.x+Settings.scale/2,myShip.loc.x+Settings.scale};
            int[] yPoints = {myShip.loc.y+Settings.scale,myShip.loc.y,myShip.loc.y+Settings.scale};
            g.drawPolygon(xPoints, yPoints, 3);
            
        
        }else{
            
            
            for (i = 0; i < Settings.scale; i++){
                
                
                switch (generator.nextInt(2)){
                    case 0:
                        g.setColor(Color.YELLOW);
                        break;
                    default:
                        g.setColor(Color.RED);
                        break;
                }
                
                
                g.fillOval(myShip.loc.x+i, myShip.loc.y+Settings.scale*generator.nextInt(10)/10, 3, 3);
            }
        }
    }
    

    public static void drawProjectiles(Graphics g, Point myProjectiles[]){
        int i;
        
        
        for (i = 0; i < myProjectiles.length; i++){
            
           
            if (myProjectiles[i] != null){
                
                
                if (Settings.superLaser){
                    g.setColor(Color.BLUE);
                    g.fillRect(myProjectiles[i].x, myProjectiles[i].y, Settings.scale/5, Settings.scale);
                    
                
                }else{
                    g.setColor(Color.YELLOW);
                    g.fillOval(myProjectiles[i].x, myProjectiles[i].y, Settings.scale/5, Settings.scale/5);
                }
            }
        }
    }
}