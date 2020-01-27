import java.io.*;
import javax.swing.*;


class HighScores{
    
    public Frame myFrame;
    
    private String names[];    
    private int scores[];
    
    public HighScores(){        
        File hsFile;
        BufferedReader inStream;
        String inString = "";
        int nameStart;
        int count = 0;
        
        names = new String[Settings.numScores];
        scores = new int[Settings.numScores];
        
       
        hsFile = new File(Settings.highScoresFileName);
        if (!hsFile.exists()){
           
            try{
                hsFile.createNewFile();
            }catch(Exception e){
                System.out.println("Error creating file " + Settings.highScoresFileName);
                System.out.println(e);
                return;
            }
            for (int i = 0; i < Settings.numScores; i++){
                scores[i] = 0;
                names[i] = "nobody";
            }
            
        }else{
           
            try{
                inStream = new BufferedReader(new FileReader(Settings.highScoresFileName));
            }catch(Exception e){
                System.out.println("Error reading file " + Settings.highScoresFileName);
                System.out.println(e);
                return;
            }
            
            
            try{
                inString = inStream.readLine();
            }catch(Exception e){}
            while ((inString != null) && (count < Settings.numScores)){
                nameStart = inString.indexOf('\t');
                scores[count] = Integer.valueOf(inString.substring(0,nameStart));
                names[count] = inString.substring(nameStart+1, inString.length());
                try{
                    inString = inStream.readLine();
                }catch(Exception e){}
                count++;
            }
            
            
            try{
                inStream.close();
            }catch(Exception e){
                System.out.println("Error closing file " + Settings.highScoresFileName);
                System.out.println(e);
            }
        }
    }
    
   
    public void showHighScores(String name, int score){
        String highScoresString = "";
        
        for (int i = 0; i < names.length; i++){
            
            if ((names[i].equals(name)) && 
                 (score == scores[i])){
                highScoresString += ">>>" + names[i] + " - " + scores[i] + "<<<\n";
            }else{
                highScoresString += names[i] + " - " + scores[i] + "\n";
            }
        }
        
        JOptionPane.showMessageDialog(myFrame,
                                      highScoresString,
                                      "Game Over",
                                      JOptionPane.PLAIN_MESSAGE);
    }
    
    
    public void addHighScore(int score){
        String name = "";
        
        
        if (score > scores[scores.length-1]){
            name = JOptionPane.showInputDialog(myFrame, "Game Over");
             if (name != null){
                 scores[scores.length-1] = score;
                 names[scores.length-1] = name;
                 sortScores();
                 showHighScores(name, score);
             }
        }
    }
    
    
    public void sortScores(){
        String tempName;
        int tempScore;
        
        
        for (int i = scores.length - 1; i > 0; i--){
            if (scores[i] > scores[i-1]){
                tempName = names[i];
                tempScore = scores[i];
                names[i] = names[i-1];
                scores[i] = scores[i-1];
                names[i-1] = tempName;
                scores[i-1] = tempScore;
            }            
        }
    }
    
    
    public void writeScores(){
        File hsFile;
        BufferedWriter outStream;
        
        
        hsFile = new File(Settings.highScoresFileName);
        if (!hsFile.exists()){
            System.out.println(Settings.highScoresFileName + " does not exist.");
            return;
        }
        
       
        try{
            outStream = new BufferedWriter(new FileWriter(Settings.highScoresFileName));
        }catch(Exception e){
            System.out.println("Error reading file " + Settings.highScoresFileName);
            System.out.println(e);
            return;
        }
        
        
        try{
            for(int i = 0; i < Settings.numScores; i++){
                outStream.write(scores[i] + "\t" + names[i] + "\n");
            }
        }catch(Exception e){}
        
        
        try{
            outStream.close();
        }catch(Exception e){
            System.out.println("Error closing file " + Settings.highScoresFileName);
            System.out.println(e);
        }
    }
}