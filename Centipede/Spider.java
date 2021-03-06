import java.awt.*;
import java.util.*;


public class Spider{
    
    public Point segments[];
    
   
    public int horizontal;
    
    
    public int vertical;
    
    
    public int length;
    public int health;
    
    public Spider (int inLength, int inHorizontal, int inVertical){
        length = Settings.SpiderStartSize;
        horizontal = inHorizontal;
        vertical = inVertical;
        segments = new Point[length];
        this.health=2;
    }
    
    
    public int contains(Point testLoc){     
        for (int i = 0; i < length; i++){
            if ((segments[i].x == testLoc.x) &&
                (segments[i].y == testLoc.y)){
                return i;
            }
        }
        return -1;
    }
}