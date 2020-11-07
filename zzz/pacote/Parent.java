package zzz.pacote;

import zzz.MainAct;

public class Parent {

  public static int maxTimesRan = 3;
  
  static {
    System.out.println("2");
	}

  public Parent()
  {
    MainAct.maxTimesRan = 4;
  }  
}
