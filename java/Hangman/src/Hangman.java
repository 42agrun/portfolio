import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import static java.lang.System.exit;

public class Hangman{
    public static final String RED = "\u001B[31m";
    public static final String GREEN = "\u001B[32m";
    public static final String YELLOW = "\u001B[33m";
    public static final String RESET = "\u001B[0m";
    protected static String word = "";
    protected static StringBuilder guessed = new StringBuilder();
    protected static int attempts = 7;
    public static void chooseWord(){
        //Selecting a number between 1 and 150 for the wordlist
        int number = (int)(Math.random() * 150 + 1);
        FileInputStream file;
        try{
            file = new FileInputStream("words.txt");
            BufferedReader reader = new BufferedReader(new InputStreamReader(file));
            String buffer;
            int n = 1;
            try {
                while ((buffer = reader.readLine()) != null) {
                    if (n == number){
                        word = buffer.toLowerCase();
                        break;
                    }
                    else
                        n++;
                }
                reader.close();
            } catch (IOException e){
                System.out.println(RED + "Error encountered while reading 'Words.txt'. Quitting now!" + RESET);
                reader.close();
                exit(1);
            }
        }
        catch (IOException e){
            System.out.println(RED + "Error encountered while preparing the game. 'Words.txt' is missing?" + RESET);
            exit(1);
        }
    }

    public static void printWord(){
        int len = word.length();
        boolean complete = true;
        boolean found;
        System.out.print("Current word: ");
        for (int i = 0; i < len; i++){
            char c = word.charAt(i);
            found = false;
            for (int x = 0; x < guessed.length(); x++){
                if (c == guessed.charAt(x)){
                    System.out.print(GREEN + c + " " + RESET);
                    found = true;
                    break;
                }
            }
            if (!found) {
                System.out.print(GREEN + "_ " + RESET);
                complete = false;
            }
        }
        if (complete){
            System.out.println();
            System.out.println(GREEN + "Congratulations, you guessed the word! Quitting now." + RESET);
            exit(0);
        }
        System.out.println(RESET + "(Remaining attempts: " + attempts + ")");
    }

    public static void main(String ... args){
        System.out.println("Welcome to Hangman! Can you guess the word which I'll choose?");
        chooseWord();
        while (attempts > 0){
            printWord();
            char c = 0;
            System.out.println(YELLOW + "Please enter a single letter which you'd like to insert." + RESET);
            while (true){
                Scanner scanner = new Scanner(System.in);
                String character = scanner.nextLine();
                character = character.toLowerCase();
                if (!character.isEmpty())
                    c = character.charAt(0);
                if (character.length() != 1 || Character.isWhitespace(c) || !Character.isLetter(c)){
                    System.out.println(RED + "Try again! Please type in a single letter!" + RESET);
                }
                else {
                    boolean dupe = false;
                    for (int i = 0; i < guessed.length(); i++){
                        if (guessed.charAt(i) == c && !dupe){
                            dupe = true;
                            System.out.println(RED + "You've already used this letter! Guess again!" + RESET);
                        }
                    }
                    if (!dupe){
                        guessed.append(c);
                        break;
                    }
                }
            }
            boolean exists = false;
            for (int i = 0; i < word.length(); i++){
                if (c == word.charAt(i)) {
                    exists = true;
                    break;
                }
            }
            if (!exists){
                System.out.println(RED + "Sorry, that letter doesn't exist in my word!" + RESET);
                attempts--;
            }
        }
        System.out.println(YELLOW + "You ran out of attempts! The word I was looking for was: " + RESET + word);
    }
}