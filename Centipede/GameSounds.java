import java.io.*;
import java.net.URL;
import javax.sound.sampled.*;


public class GameSounds{
    
    Clip cannon;
    Clip laser;
    Clip shipExplode;
    Clip centDie;
    Clip shroomHit;
    Clip newGame;
    Clip nextLevel;
    Clip gameOver;
        
    public GameSounds(){
        
        URL url;
        AudioInputStream audioIn;
        
        try{
                  
            url = this.getClass().getClassLoader().getResource("cannon.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            cannon = AudioSystem.getClip();
            cannon.open(audioIn);
            
              
            url = this.getClass().getClassLoader().getResource("laser.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            laser = AudioSystem.getClip();
            laser.open(audioIn);
            
                   
            url = this.getClass().getClassLoader().getResource("shipExplode.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            shipExplode = AudioSystem.getClip();
            shipExplode.open(audioIn);
            
                  
            url = this.getClass().getClassLoader().getResource("centDie.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            centDie = AudioSystem.getClip();
            centDie.open(audioIn);
            
               
            url = this.getClass().getClassLoader().getResource("shroomHit.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            shroomHit = AudioSystem.getClip();
            shroomHit.open(audioIn);
            
                 
            url = this.getClass().getClassLoader().getResource("newGame.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            newGame = AudioSystem.getClip();
            newGame.open(audioIn);
            
              
            url = this.getClass().getClassLoader().getResource("nextLevel.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            nextLevel = AudioSystem.getClip();
            nextLevel.open(audioIn);
            
                   
            url = this.getClass().getClassLoader().getResource("gameOver.wav");
            audioIn = AudioSystem.getAudioInputStream(url);
            gameOver = AudioSystem.getClip();
            gameOver.open(audioIn);
        }catch(Exception e){}
    }
    
    
    public void cannon(){
        if(cannon==null){
            return;
        }
        cannon.stop();
        cannon.setFramePosition(0);
        cannon.start();
    }
    
    
    public void laser(){
        laser.stop();
        laser.setFramePosition(0);
        laser.start();
    }
    
    
    public void shipExplode(){
        if(shipExplode==null){
            return;
        }
        shipExplode.stop();
        shipExplode.setFramePosition(0);
        shipExplode.start();
    }
    
    
    public void centDie(){
        if(centDie==null){
            return;
        }
        centDie.stop();
        centDie.setFramePosition(0);
        centDie.start();
    }
    
    
    public void shroomHit(){
        if(shroomHit==null){
            return;
        }
        shroomHit.stop();
        shroomHit.setFramePosition(0);
        shroomHit.start();
    }
    
  
    public void newGame(){
        if(newGame==null){
            return;
        }
        newGame.stop();
        newGame.setFramePosition(0);
        newGame.start();
    }
    
   
    public void nextLevel(){
        if(nextLevel==null){
            return;
        }
        nextLevel.stop();
        nextLevel.setFramePosition(0);
        nextLevel.start();
    }
    
   
    public void gameOver(){
        if(gameOver==null){
            return;
        }
        gameOver.stop();
        gameOver.setFramePosition(0);
        gameOver.start();
    }
}