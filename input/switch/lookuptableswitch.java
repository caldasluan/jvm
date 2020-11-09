// compile with "javac -source 8 -target 8 input/switch/lookuptableswitch.java"

public class lookuptableswitch {

  public static int lookup(int i)
  {
    switch(i)
    {
      case -8000:
        return 372;
      case 4:
        return 3;
      case 2000000:
        return 420;
      default:
        return 0;
    }
  }
  
  public static void main(String[] args) {
    System.out.println(lookup(0));
    System.out.println(lookup(1));
    System.out.println(lookup(4));
    System.out.println(lookup(-3));
    System.out.println(lookup(-8000));
    System.out.println(lookup(-8001));
    System.out.println(lookup(2000000));
    System.out.println(lookup(3000000));
  }
}
