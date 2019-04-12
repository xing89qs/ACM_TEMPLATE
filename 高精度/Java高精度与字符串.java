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
System.out.println(x);
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
		BigInteger[][] dp = new BigInteger[105][1005];
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
//常量定义：
static BigInteger ONE	//大整数 1
static BigInteger TEN	//大整数 10
static BigInteger ZERO	//大整数 0
//主要有以下方法可以使用：
BigInteger abs()	//绝对值（abs(this)）
BigInteger add(BigInteger val)	//加法（this + val）
BigInteger subtract(BigInteger val)	//减法（this - val）
BigInteger multiply(BigInteger val)	//乘法（this * val）
BigInteger divide(BigInteger val)	//除法（this / val）
BigInteger [] dividedandRemainder(BigInteger val)	//余数和商（返回一个数组：第一位是商，第二位是余数）
BigInteger pow(BigDecimal val)	//val次幂（this ** val）
BigInteger mod(BigInteger val)	//对val取模（this % val）
BigInteger gcd(BigInteger val)	//最大公约数（gcd(this, val)）
BigInteger and(BigInteger val)	//取与（this & val）
BigInteger andNot(BigInteger val)	//与反（this & ~val）
BigInteger not()	//取反（~this）
BigInteger or(BigInteger val)	//取或（this | val）
BigInteger xor(BigInteger val)	//取或（this ^ val）
BigInteger shiftLeft(int n)	//左移（this << n）
BigInteger shiftRight(int n)	//右移（this >> n）
BigInteger max(BigInteger val)	//取最大值（max(this, val)）
BigInteger min(BigInteger val)	//取最小值（min(this, val)）
BigInteger modInverse(BigInteger m)	//求逆元（this**(-1) % m）
BigInteger modPow(BigInteger exponent, BigInteger m)	//求模幂（this**exponent % m）
int compareTo(BigInteger val)	//相当于 x 与 val 比较（this CMP val）
boolean equals(Object x)	//判断是否相等（this == x）
static BigInteger valueOf(long val)	//把val转化为大整数值
//输出数字时直接使用 System.out.println(a) 即可
int	intValue()	//转换为整形变量
long longValue()	//转换为长整形变量
String toString()	//转换为字符串

/*BigDecimal*/
BigDecimal add(BigDecimal val)
BigDecimal subtract(BigDecimal val)
BigDecimal multiply(BigDecimal val)
BigInteger divide(BigInteger val)
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