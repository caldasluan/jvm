package input.statics;

public interface StaticInt2 extends StaticInt3 {

  public static void i2s1()
  {
    System.out.println("i2s1");
  }

  public default void i2i1()
  {
    System.out.println("i2i1");
  }

  public default void i2i2()
  {
    System.out.println("i2i2");
  }
}
