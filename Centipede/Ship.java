import java.awt.*;


public class Ship{
    
    public Point tryLoc;
    
    
    public Point loc;
    
    
    public int lives;
    
    
    public boolean firing;
    
   
    public int invulnerableTime;
    
   
    private Point myProjectiles[];
    
    
    private GameSounds myGameSounds;
    
    
    public Ship(GameSounds inGameSounds, Point inProjectiles[]){
        myProjectiles = inProjectiles;
        myGameSounds = inGameSounds;
        
        loc = new Point(Settings.shipStartLoc.x, Settings.shipStartLoc.y);
        tryLoc = new Point(loc.x, loc.y);
        lives = Settings.startLives;
        invulnerableTime = 0;
    }
    
   
    public void fire(){
        if (invulnerableTime == 0){
            for (int i = 0; i < Settings.maxProjectiles; i++){
                if (myProjectiles[i] == null){
                    myProjectiles[i] = new Point((int) Math.round(loc.x + Settings.scale / 2.0), (int) Math.round(loc.y));
                    if (Settings.superLaser){
                        myGameSounds.laser();
                    }else{
                        myGameSounds.cannon();
                    }
                    break;
                }
            }
        }
    }
}