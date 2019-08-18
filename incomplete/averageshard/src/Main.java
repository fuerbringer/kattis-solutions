/*
 * Implementation works, but is not fast enough for Kattis ¬(<1.0s)
 */
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

public class Main {
  public static final double schoolAvg(List<Integer> iqs) {
    double sum = 0;
    for(int iq : iqs) {
      sum += iq;
    }
    return sum / iqs.size();
  }

  /* Core problem logic */
  public static final int calcMaxTransfers(List<Integer> cs, List<Integer> e) {
    final double avgcs0 = schoolAvg(cs);
    final double avge0 = schoolAvg(e);
    int transfers = 0;

    for(int i = 0; i < cs.size(); i++) {
      // Build situation when we transfer student with iq at cs[i]
      List<Integer> newCs = new ArrayList<Integer>(cs);
      List<Integer> newE = new ArrayList<Integer>(e);
      newCs.remove(i);
      newE.add(cs.get(i));
      final double avgcs1 = schoolAvg(newCs);
      final double avge1 = schoolAvg(newE);
      if(avgcs1 > avgcs0 && avge1 > avge0) {
        transfers++;
      }
    }
    return transfers;
  }

  public static void main(String[] args) {
    final Scanner sc = new Scanner(System.in);
    final int tests = new Integer(sc.nextLine());
    String s;
    List<Integer> res = new ArrayList<Integer>();
    int l = 0;

    for(int i = 0; i < tests; i++) {
      List<Integer> cs = new ArrayList<Integer>();
      List<Integer> e = new ArrayList<Integer>();

      while(l < 4) {
        s = sc.nextLine();
        if(!s.equals("")) {
          switch(l) {
            case 1:
              // N_CS and N_E
              // no op
              break;
            case 2:
              // Values for CS
              final String[] csTmp = s.split(" ");
              for(String csTmpI : csTmp) {
                cs.add(new Integer(csTmpI));
              }
              break;
            case 3:
              // Values for E
              final String[] eTmp = s.split(" ");
              for(String eTmpI : eTmp) {
                e.add(new Integer(eTmpI));
              }
              break;
          }
        }
        l++;
      }

      //System.out.println(schoolAvg(cs));
      //System.out.println(schoolAvg(e));
      res.add(calcMaxTransfers(cs, e));

      l = 0;
    }
    for(int r : res) {
      System.out.println(r);
    }
  }
}
