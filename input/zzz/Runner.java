package input.zzz;
public interface Runner extends Runner2, Runner3 {
  public void run();
  public String what = "Manowhat";
  default void doNothing() {
    System.out.println(what);
  }
}