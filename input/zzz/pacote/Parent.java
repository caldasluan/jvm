package input.zzz.pacote;

import input.zzz.MainAct;

public class Parent {

  public static int maxTimesRan = 3;
  
  static {
    System.out.println("2");
	}

  public Parent()
  {
    MainAct.maxTimesRan = 4;
  }
  
  public void po()
  {
		System.out.print("VSF ");
		System.out.println(2);
  }
}
