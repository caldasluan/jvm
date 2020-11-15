package input.cast;

// compile with "javac -source 8 -target 8 input/cast/Instanceof.java"

import input.heranca.*;

public class Instanceof  {
  public static void main(String[] args) {
    // Verifica arvore de heranca completa
    Classe1 c1 = new Classe1();
    System.out.print("Classe1 ");
    System.out.println(c1 instanceof Classe1);
    System.out.print("Classe2 ");
    System.out.println(c1 instanceof Classe2);
    System.out.print("Classe3 ");
    System.out.println(c1 instanceof Classe3);
    System.out.print("Inter1 ");
    System.out.println(c1 instanceof Inter1);
    System.out.print("Inter2 ");
    System.out.println(c1 instanceof Inter2);
    System.out.print("Inter3 ");
    System.out.println(c1 instanceof Inter3);
    System.out.print("Inter4 ");
    System.out.println(c1 instanceof Inter4);
    System.out.print("Inter5 ");
    System.out.println(c1 instanceof Inter5);
    System.out.print("Object ");
    System.out.println(c1 instanceof Object);
    System.out.print("Instanceof ");
    System.out.println((Object)c1 instanceof Instanceof);

    System.out.println("\nTestes com arrays e matrizes\n");

    char char_array[] = new char[8];
    System.out.print("char[] ");
    System.out.println(char_array instanceof char[]);
    System.out.print("Object ");
    System.out.println(char_array instanceof Object);

    // Verifica heranca entre arrays
    String string_matriz[][][] = new String[1][1][1];
    string_matriz[0][0][0] = "a";

    System.out.print("\nString[][][] ");
    System.out.println(string_matriz instanceof String[][][]);

    int matriz[][] = new int[3][3];
    matriz[0][0] = 1;
  }
}
