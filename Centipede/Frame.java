import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;


public class Frame extends JFrame implements MenuListener, ActionListener{
    private static final long serialVersionUID = 1L;

    
    private GameCanvas myGameCanvas;
    
    
    private GameLogic myGameLogic;
        
   
    private HighScores myHighScores;
    
    private JMenuBar bar;
        
    
    private JMenu file;
        
    
    private JMenuItem newGame;
        
    
    public JMenuItem pauseGame;
        
    
    private JMenuItem exitGame;
        
    
    private JMenu options;
        
    
    private JRadioButtonMenuItem easyDifficulty;
        
    
    private JRadioButtonMenuItem mediumDifficulty;
        
    
    private JRadioButtonMenuItem hardDifficulty;
        
   
    private JMenuItem superLaser;
        
   
    private JMenuItem highScores;
    
    
    public Frame(GameLogic inGameLogic, GameCanvas inGameCanvas, HighScores inHighScores){
        myGameCanvas = inGameCanvas;
        myGameLogic = inGameLogic;
        myHighScores = inHighScores;
        
       
        newGame = new JMenuItem("New Game");
        newGame.addActionListener(this);
        pauseGame = new JMenuItem("Pause Game");
        pauseGame.addActionListener(this);
        exitGame = new JMenuItem("Exit Game");
        exitGame.addActionListener(this);        
        file = new JMenu("File");
        file.addMenuListener(this);
        file.add(newGame);
        file.add(pauseGame);
        file.add(exitGame);
        
        
        easyDifficulty = new JRadioButtonMenuItem("Easy");
        easyDifficulty.addActionListener(this);
        easyDifficulty.setSelected(false);
        mediumDifficulty = new JRadioButtonMenuItem("Medium");
        mediumDifficulty.addActionListener(this);
        mediumDifficulty.setSelected(true);
        hardDifficulty = new JRadioButtonMenuItem("Hard");
        hardDifficulty.addActionListener(this);
        hardDifficulty.setSelected(false);
        superLaser = new JMenuItem("Super Laser is OFF");
        superLaser.addActionListener(this);
        options = new JMenu("Options");
        options.addMenuListener(this);
        options.add(easyDifficulty);
        options.add(mediumDifficulty);
        options.add(hardDifficulty);
        options.addSeparator();
        options.add(superLaser);
        
        
        highScores = new JMenuItem("High Scores");
        highScores.addActionListener(this);
        
        
        bar = new JMenuBar();
        bar.add(file);
        bar.add(options);
        bar.add(highScores);
        
        
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setJMenuBar(bar);
        setLocation(100,100);
        setResizable(false);
        
        
        add(myGameCanvas.c);
        
        
        pack();
        
       
        setVisible(true);
    }
    
    
    public void menuCanceled(MenuEvent e){
    }
    
    
    public void menuDeselected(MenuEvent e){
    }
    
   
    public void menuSelected(MenuEvent e){
        Object ob = e.getSource();
        
    }
    
    
    public void actionPerformed(ActionEvent e){
        Object ob = e.getSource();
        
      
        if (ob == newGame){
            myGameLogic.syncReset = true;
        }else if (ob == highScores){
            highScores.setSelected(false);
            myGameLogic.paused = true;
            pauseGame.setText("Unpause Game");
            myHighScores.showHighScores("", 0);
            myGameLogic.paused = false;
            pauseGame.setText("Pause Game");
            
        
        }else if (ob == pauseGame){
            if (myGameLogic.paused){
                myGameLogic.paused = false;
                pauseGame.setText("Pause Game");
            }else{
                myGameLogic.paused = true;
                pauseGame.setText("Unpause Game");
            }
        
       
        }else if (ob == exitGame){
            myHighScores.writeScores();
            System.exit(0);
            
       
        }else if (ob == superLaser){
            if (Settings.superLaser){
                superLaser.setText("Super Laser is OFF");
                Settings.superLaser = false;
            }else{
                superLaser.setText("Super Laser is ON");
                Settings.superLaser = true;
            }
            
       
        }else if(ob == easyDifficulty){
            easyDifficulty.setSelected(true);
            mediumDifficulty.setSelected(false);
            hardDifficulty.setSelected(false);
            myGameLogic.difficulty = Settings.centDelayEasy;
            Settings.centDelay = (int) Math.round(myGameLogic.difficulty / Math.pow(Settings.levelFactor, myGameLogic.level));
            
      
        }else if(ob == mediumDifficulty){
            easyDifficulty.setSelected(false);
            mediumDifficulty.setSelected(true);
            hardDifficulty.setSelected(false);
            myGameLogic.difficulty = Settings.centDelayMedium;
            Settings.centDelay = (int) Math.round(myGameLogic.difficulty / Math.pow(Settings.levelFactor, myGameLogic.level));
            
       
        }else if(ob == hardDifficulty){        
            easyDifficulty.setSelected(false);
            mediumDifficulty.setSelected(false);
            hardDifficulty.setSelected(true);
            myGameLogic.difficulty = Settings.centDelayHard;
            Settings.centDelay = (int) Math.round(myGameLogic.difficulty / Math.pow(Settings.levelFactor, myGameLogic.level));
        }
    }
}