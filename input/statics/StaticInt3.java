package input.statics;

public interface StaticInt3 {
  
  public static void i3s1()
  {
    System.out.println("i3s1");
  }

  public default void i3i1()
  {
    System.out.println("i3i1");
  }

  public default void i3i2()
  {
    System.out.println("i3i2");
  }
}
