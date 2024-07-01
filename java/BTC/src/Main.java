import java.util.Scanner;

public class Main {

    public static int createNumber(String date){
        String string = "";
        for (int i = 0; i < date.length(); i++){
            if (date.charAt(i) >= '0' && date.charAt(i) <= '9'){
                string += date.charAt(i);
            }
        }
        return Integer.parseInt(string);
    }
    public static float compareTables(InputTable table, String date, float value){
        int newDate = createNumber(date);
        int [] dates = new int[table.id];
        for (int i = 0; i < table.id; i++)
            dates[i] = createNumber(table.table.get(i).getDate());
        int id = 0;
        int diff = dates[0] - newDate;
        if (diff < 0)
            diff *= -1;
        for (int i = table.id - 1; i > -1; i--) {
            if (newDate == dates[i]){
                id = i;
                break;
            }
            if (newDate < dates[i]){
                int filter = dates[i] - newDate;
                if (filter < 0)
                    filter *= -1;
                if (filter < diff){
                    diff = filter;
                    id = i;
                }
            }
        }
        return table.table.get(id).getValue() * value;
    }
    public static void printBTC(InputTable table, InputTable input){
        System.out.println("#ID    Date          BTC          €");
        System.out.println("==========================================");
        int length;
        for (int i = 0; i < input.id; i++) {
            if (input.table.get(i).getID() < 100)
                System.out.print("0");
            if (input.table.get(i).getID() < 10)
                System.out.print("0");
            System.out.print(input.table.get(i).getID() + "    ");
            System.out.print(input.table.get(i).getDate() + " ");
            if (!input.table.get(i).getDate().contains("!"))
                System.out.print("   ");
            length = String.valueOf(input.table.get(i).getValue()).length();
            System.out.print(input.table.get(i).getValue());
            for (int x = 9; x > length; x--)
                System.out.print(" ");
            System.out.print("=>  ");
            if (input.table.get(i).getDate().contains("!"))
                System.out.println("Invalid formatting!");
            else
                System.out.println(compareTables(table, input.table.get(i).getDate(), input.table.get(i).getValue()));
        }
    }

    //Debug method
    public static void printTable(InputTable table){
        for (int i = 0; i < table.id; i++){
            System.out.print(table.table.get(i).getID() + ": ");
            System.out.print(table.table.get(i).getDate() + " | ");
            System.out.println(table.table.get(i).getValue());
        }
    }

    public static void main(String[] args) {
        String string;
        System.out.println("Please enter a valid filepath for BTC calculation!");
        while (true)
        {
            Scanner scanner = new Scanner(System.in);
            string = scanner.nextLine();
            if (string.trim().isEmpty()){
                System.out.println("Faulty input. Please try again.");
            }
            else
                break;
        }
        InputTable stock = new InputTable("data.csv");
        InputTable input = new InputTable(string);
        printBTC(stock, input);
    }
}