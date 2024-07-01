import java.io.*;
import java.util.ArrayList;

import static java.lang.System.exit;
public class InputTable {
    public ArrayList<TripleArray> table = new ArrayList<>();
    public int id = 0;

    //XXXX-XX-XX is the expected format for dates
    public String [] checkFormat(String [] str){
        String day = "";
        String month = "";
        boolean faulty = false;

        char [] nbr = str[0].toCharArray();
        int len = nbr.length - 1;
        if (len != 9)
            faulty = true;

        for (int i = 0; i < len + 1; i++){
            if ((i == 4 || i == 7) && nbr[i] != '-')
                faulty = true;
            else if ((i != 4 && i != 7) && (nbr[i] > '9' || nbr[i] < '0')) {
                str[0] += "(!)";
                return str;
            }
            i++;
        }
        month += nbr[len-4];    //XXXX-YY-XX
        month += nbr[len-3];
        day += nbr[len-1];      //XXXX-XX-YY
        day += nbr[len];

        int m = Integer.parseInt(month);
        int d = Integer.parseInt(day);
        if (m < 1 || m > 12)    //there are only 12 months
            faulty = true;
        if (d < 1 || d > 31)    //no month can have more than 31 days
            faulty = true;
        if (faulty)
            str[0] += "(!)";
        return str;
    }
    public String [] splitLine(String line){
        int size = line.length();
        char [] string = line.toCharArray();
        char [][] split = new char[2][100];
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < size && j < 2){
            if (string[i] != ',' && string[i] != '|' && string[i] != 0){
                split[j][k] = string[i];
                k++;
            }
            else {
                j++;
                k = 0;
            }
            i++;
        }
        String [] newStr = new String[2];
        for (int x = 0; x < j + 1 && x < 2; x++){
            newStr[x] = String.valueOf(split[x]).trim();
        }
        newStr = checkFormat(newStr);
        return newStr;
    }
    public void decipherLine(String line){
        if (line.contains("date") || line.contains("exchange rate")){
            return ;
        }
        String [] split = splitLine(line);
        TripleArray triplet = new TripleArray(++id, split[0], Float.parseFloat(split[1]));
        table.add(triplet);
    }
    public InputTable(String filename){
        super();
        FileInputStream stream;
        try {
            stream = new FileInputStream(filename);
            BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
            String buffer;
            try {
                while ((buffer = reader.readLine()) != null) {
                    decipherLine(buffer.trim());
                }
                reader.close();
            } catch (IOException e){
                reader.close();
                System.out.println("Error encountered while reading line! Quitting program.");
                exit(1);
            }
        }
        catch (IOException e){
            System.out.println(filename + " could not be found! Quitting program.");
            exit(1);
        }
    }
}