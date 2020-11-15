package input.joga;

// compile with "javac -source 8 -target 8 input/joga/joga.java"

public class joga {

  public static void teste() throws Exception
  {
    throw new Exception();
  }
  public static void main(String[] args) {
    try {
      teste();
      System.out.println("Nao funciona");
    } catch (Exception e) {
      System.out.println("Funciona");
    }
  }
}
