package input.zzz;

import input.zzz.pacote.Parent;

// compile with "javac -source 8 -target 8 input/zzz/MainAct.java"

public class MainAct extends Parent implements Runner {

	public static final int seiLa = 4123213;

	public final int teste = 3;

	private int timesRan;

	private static Helper putz;

	static {
		System.out.println("1");
	}

	public void run() {
		if (timesRan == maxTimesRan) {
			System.out.println("Fim");
		} else {
			timesRan++;
			System.out.print("Run number ");
			System.out.println(timesRan);
			run();
			return;
		}
		putz = new Helper();
		putz.HelperCode = -timesRan;
	}
	
	public static void staticMethod(long a)
	{
		System.out.println("3");
	}

	public static void main(String args[]) {

		for(int i = 0; i < args.length; i++)
		{
			System.out.println(args[i]);
		}
		
		Runner runner = new MainAct();
		MainAct ma = (MainAct)runner;

		try
		{
			ma.ehIsso();
		} catch(Exception exc) {}
	}

	public void po()
	{
		System.out.print("VSF ");
		System.out.println(1);
	}

	public void nop() {}
	public void pon() {}

	public class Helper
	{
		public int HelperCode;
		public Helper()
		{

		}
	}
}
