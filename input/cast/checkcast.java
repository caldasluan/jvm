package input.cast;

// compile with "javac -source 8 -target 8 input/cast/checkcast.java"

import input.heranca.*;

public class checkcast {

  public static void daErro()
  {
    int a = 1/0;
  }
  
  public static void main(String[] args) {
    Classe1 manokkk = new Classe1();
    Object c1 = manokkk;
    System.out.print("Classe1 ");
    Classe1 c = (Classe1)c1;
    System.out.print("Classe2 ");
    Classe2 c2 =(Classe2)c1;
    System.out.print("Classe3 ");
    Classe3 c3 =(Classe3)c1;
    System.out.print("Inter1 ");
    Inter1 i1 = (Inter1)c1;
    System.out.print("Inter2 ");
    Inter2 i2 = (Inter2)c1;
    System.out.print("Inter3 ");
    Inter3 i3 = (Inter3)c1;
    System.out.print("Inter4 ");
    Inter4 i4 = (Inter4)c1;
    System.out.print("Inter5 ");
    Inter5 i5 = (Inter5)c1;
    System.out.print("Object ");
    Object o = (Object)c1;
    System.out.print("Instanceof ");
    try{
      Object o2 = ((Instanceof)(Object)c1);
    } catch(Exception e) {
      System.out.println("Exception");
    }

    try{
      daErro();
    } catch(Exception e) {
      System.out.println("Outra exception");
    }
    
    Object o2 = ((Instanceof)(Object)c1);
  }
  public class Teste{}
}
