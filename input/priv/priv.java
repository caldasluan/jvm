package input.priv;

// compile with "javac -source 8 -target 8 input/priv/priv.java"

public class priv {
  
  private void p1()
  {
    System.out.println("p1");
  }

  public static void main(String[] args) {
    priv p = new priv();
    p.p1();
  }
}
