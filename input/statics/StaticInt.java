package input.statics;

public interface StaticInt {

  public static void is1()
  {
    System.out.println("is1");
  }

  public default void ii1()
  {
    System.out.println("ii1");
  }

  public default void ii2()
  {
    System.out.println("ii2");
  }
}
