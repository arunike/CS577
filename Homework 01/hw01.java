import java.util.Scanner;

public class hw1 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String string = scan.nextLine().trim();
        int line = Integer.parseInt(string);
        String[] name = new String[line];

        for(int i = 0; i < line; i++) {
            name[i] = scan.nextLine();
        }

        scan.close();
        
        for(int i = 0; i < line; i++) {
            System.out.println("Hello, " + name[i] + "!");
        }
    }
}