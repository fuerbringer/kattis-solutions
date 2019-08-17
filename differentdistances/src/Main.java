import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

public class Main {
  public static final double pNormDistance(final double x1, final double y1,
      final double x2, final double y2, final double p) {
    final double x = Math.pow(Math.abs(x1 - x2), p);
    final double y = Math.pow(Math.abs(y1 - y2), p);
    final double inner = x + y;
    final double res = Math.pow(inner, 1 / p);
    return res;
  }

  public static void main(String[] args) {
    final Scanner sc = new Scanner(System.in);
    String s;
    final List<Double> results = new ArrayList<Double>();
    do {
      s = sc.nextLine();
      final String[] line = s.split(" ");
      if(line.length >= 5) {
        final double lineRes = pNormDistance(new Double(line[0]), new
            Double(line[1]), new Double(line[2]), new Double(line[3]), new
            Double(line[4]));
        results.add(lineRes);
      }
    } while(!s.equals("0"));

    for(final double r : results) {
      System.out.printf("%.10f%n", r);
    }
  }
}
