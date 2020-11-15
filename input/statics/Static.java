package input.statics;

// compile with "javac -source 8 -target 8 input/statics/Static.java"

public class Static extends StaticPai implements StaticInt {

  public static void s1()
  {
    System.out.println("s1");
  }
  
  public void i1()
  {
    System.out.println("i1");
  }

  public void ii2()
  {
    System.out.println("new ii2");
  }
  
  public static void main(String[] args) {
    Static.s1();
    Static.s2();

    StaticInt.is1();
    StaticInt2.i2s1();
    StaticInt3.i3s1();

    Static s = new Static();
    s.i1();
    s.i2();
    s.ii1();
    s.ii2();
    s.i2i1();
    s.i2i2();
    s.i3i1();
    s.i3i2();
  }
}
