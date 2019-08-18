import java.util.Scanner;
import java.lang.Math;

public class Main {
  public static void main(String[] args) {
    final Scanner sc = new Scanner(System.in);
    final String s = sc.nextLine();
    final String[] ss = s.split(" ");
    final int a = Integer.parseInt(ss[0]);
    final int b = Integer.parseInt(ss[1]);
    final int h = Integer.parseInt(ss[2]);
    int ans = Math.max(0, (int)Math.ceil(h / (double)(a - b)) - 5);
    int height = ans * (a - b);

    while(true) {
      height += a;
      ans++;
      if(height >= h) {
        break;
      }
      height -= b;
    }
    
    System.out.println(ans);
  }
}
