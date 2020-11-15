package input.invokespecial;

// compile with "javac -source 8 -target 8 input/invokespecial/invokespecial.java"

public class invokespecial extends invokespecial2 {

  public void i1()
  {
    super.i1();
    System.out.println("Segunda");
  }

  public void i2()
  {
    super.i2();
    System.out.println("sla2");
  }

  public void chamaInters()
  {
    super.inter_1();
    super.inter_2();
  }

  public static void main(String[] args) {
    invokespecial i = new invokespecial();
    invokespecial2 i2 = new invokespecial2();
    i.i1();
    i.i2();
    i2.i1();
    i.chamaInters();
  }
  
}
