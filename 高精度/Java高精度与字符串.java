/*输入*/
Scanner in = new Scanner (System.in);
Scanner in = new Scanner (new BufferedInputStream(System.in));


/*输入挂*/
class InputReader {
	BufferedReader buf;
	StringTokenizer tok;
	InputReader() {
		buf = new BufferedReader(new InputStreamReader(System.in));
	}
	boolean hasNext() {
		while (tok == null || !tok.hasMoreElements()) {
			try {
				tok = new StringTokenizer(buf.readLine());
			} catch (Exception e) {
				return false;
			}
		}
		return true;
	}
	String next() {
		if (hasNext())
			return tok.nextToken();
		return null;
	}
	int nextInt() {
		return Integer.parseInt(next());
	}
	long nextLong() {
		return Long.parseLong(next());
	}
	double nextDouble() {
		return Double.parseDouble(next());
	}
	BigInteger nextBigInteger() {
		return new BigInteger(next());
	}
	BigDecimal nextBigDecimal() {
		return new BigDecimal(next());
	}
}


/*输出*/
PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
out.println(n); 
out.printf("%.2f\n", ans);	//与c语言中printf用法相同


/*输入输出示例*/
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		Scanner cin = new Scanner (new BufferedInputStream(System.in));
		/*while(cin.hasNext()) {
			...
		}
		*/
		int n;
		n = cin.nextInt();
		BigInteger x = BigInteger.valueOf(2);
		BigInteger[] a = new BigInteger[105];
		BigInteger[][] dp = new BigInteger[105][1005];	//用i种钱凑出金额j的总方案数
		/*if(x.equals(BigInteger.ZERO)) {
			...
		}
		*/
		for(int i = 1; i <= n; i++) {
			System.out.println(x);
			x = x.multiply(x.subtract(BigInteger.valueOf(1))).add(BigInteger.valueOf(1));
		}
		cin.close();
	}
}



/*BigInteger*/
import java.math.BigInteger; 
//主要有以下方法可以使用： 
BigInteger add(BigInteger other) 
BigInteger subtract(BigInteger other) 
BigInteger multiply(BigInteger other) 
BigInteger divide(BigInteger other)
BigInteger [] dividedandRemainder(BigInteger other)	//数组第一位是商，第二位是余数
BigInteger pow(BigDecimal other)	//other次方
BigInteger mod(BigInteger other) 
BigInteger gcd(BigInteger other) 
int compareTo(BigInteger other) 
static BigInteger valueOf(long x)
//输出数字时直接使用 System.out.println(a) 即可


/*BigDecimal*/
BigDecimal add(BigDecimal other)
BigDecimal subtract(BigDecimal other)
BigDecimal multiply(BigDecimal other)
BigInteger divide(BigInteger other)
BigDecimal divide(BigDecimal divisor, int scale, BigDecimal.ROUND_HALF_UP)
BigDecimal.setScale()方法用于格式化小数点	//setScale(1)表示保留一位小数，默认用四舍五入方式


/*字符串*/
String st = "abcdefg";
char [] ch;
ch = st.toCharArray();	//字符串转换为字符数组.
for(int i = 0; i < ch.length; i++) {
	ch[i] += 1;	//字符数组可以像C++一样操作
}
System.out.println(ch);	//输入为“bcdefgh”.


/*进制转换*/
String s = Integer.toString(a, x);	//把int型数据转换乘X进制数并转换成string型
//0123456789abcdefghijklmnopqrstuvwxyz, 2<=x<=36
int b = Integer.parseInt(s, x);	//把字符串当作X进制数转换成int型


/*控制台输入输出重定向到文件*/
FileInputStream fis = new FileInputStream("b.in");  
System.setIn(fis);  
PrintStream ps = new PrintStream(new FileOutputStream("b.out"));  
System.setOut(ps);


/*Array.sort()*/
//1、Arrays.sort(int[] a, int fromIndex, int toIndex)
//这种形式是对数组部分排序，也就是对数组a的下标从fromIndex到toIndex-1的元素排序，
//注意：下标为toIndex的元素不参与排序哦！
//2、public static <T> void sort(T[] a,int fromIndex, int toIndex,  Comparator<? super T> c)
public class Main {
    public static void main(String[] args) {
        //注意，要想改变默认的排列顺序，不能使用基本类型（int,double, char）
        //而要使用它们对应的类
        Integer[] a = {9, 8, 7, 2, 3, 4, 1, 0, 6, 5};
        //定义一个自定义类MyComparator的对象
        Comparator cmp = new MyComparator();
        Arrays.sort(a, cmp);
        for(int i = 0; i < a.length; i ++) {
            System.out.print(a[i] + " ");
        }
    }
}
//Comparator是一个接口，所以这里我们自己定义的类MyComparator要implents该接口
//而不是extends Comparator
class MyComparator implements Comparator<Integer>{
    @Override
    public int compare(Integer o1, Integer o2) {
        //如果n1小于n2，我们就返回正值，如果n1大于n2我们就返回负值，
        //这样颠倒一下，就可以实现反向排序了
        if(o1 < o2) { 
            return 1;
        }else if(o1 > o2) {
            return -1;
        }else {
            return 0;
        }
    }
}
//3、lambda(仅 JAVA8 支持)
//Arrays.sort(Point[] p, int fromIndex, int toIndex, (a,b)->(a.x!=b.x?a.x-b.x:a.y-b.y))