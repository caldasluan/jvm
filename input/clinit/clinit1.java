package input.clinit;

// compile with "javac -source 8 -target 8 input/clinit/clinit1.java"

public class clinit1 {
  public static void main(String[] args) {
    System.out.println("Rodando");
    clinit2 c = new clinit2();
    System.out.println(c.a);
  }
}
