package input.cast;

// compile with "javac -source 8 -target 8 input/cast/checkcast.java"

import input.heranca.*;

public class checkcast {
  
  public static void main(String[] args) {
    Classe1 c1 = new Classe1();
    System.out.print("Classe1 ");
    System.out.println(((Classe1)c1).toString());
    System.out.print("Classe2 ");
    System.out.println(((Classe2)c1).toString());
    System.out.print("Classe3 ");
    System.out.println(((Classe3)c1).toString());
    System.out.print("Inter1 ");
    System.out.println(((Inter1)c1).toString());
    System.out.print("Inter2 ");
    System.out.println(((Inter2)c1).toString());
    System.out.print("Inter3 ");
    System.out.println(((Inter3)c1).toString());
    System.out.print("Inter4 ");
    System.out.println(((Inter4)c1).toString());
    System.out.print("Inter5 ");
    System.out.println(((Inter5)c1).toString());
    System.out.print("Object ");
    System.out.println(((Object)c1).toString());
    System.out.print("Instanceof ");
    System.out.println(((Instanceof)(Object)c1).toString());
  }
  public class Teste{}
}
