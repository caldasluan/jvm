package zzz;

import zzz.pacote.Parent;

// compile with "javac -source 8 -target 8 zzz/MainAct.java"

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

		int a = 2475558;
		float b = 2.14f;
		long c = 1000000000000L;

		int i = 1;
		a += i;
		c += i;

		int shiftar = 80, neg = -300;

		shiftar = shiftar >> 2;
		System.out.println(shiftar);
		neg = neg >> 3;
		System.out.println(neg);
		
		System.out.println(a + b - c);

		int[] array = new int[5];
		char[][] multi = new char[8][4];
		Helper[] test = new Helper[2];
		multi[2][3] = 'a';

		a /= 3 + array[2];

		Runner runner = new MainAct();
		runner.run();
		MainAct ma = (MainAct)runner;

		try
		{
			a = 3 / 0;
		}
		catch(Exception exc){}

		Parent p = new MainAct();
		p.po();

		try
		{
			ma.ehIsso();
		} catch(Exception exc) {}
		
		test[0] = ma.new Helper();

		MainAct.staticMethod(3l);

		a += putz.HelperCode + test[0].HelperCode;

		System.out.print("Kek");
		System.out.println(" SeiLa2");
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
