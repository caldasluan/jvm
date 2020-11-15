package input.ldc;

// compile with "javac -source 8 -target 8 input/ldc/ldc.java"

public class ldc {

  public static int a(int b)
  {
    return b+5;
  }

  public interface MyInterface {
    int metodo(int b);
  }

  public static void main(String[] args)
  {
    //Nao funciona
    System.out.println(true);
    MyInterface met = ldc::a;
    System.out.println(met.metodo(3));
  }
}
