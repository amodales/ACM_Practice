import java.io.*;
import java.util.*;

class Main{
	public static void main(String argv[]) throws Exception{
		Scanner in = new Scanner( System.in );
		PrintWriter out = new PrintWriter( System.out, true);
		StringBuffer ans, repeat;
		Vector<Integer> don = new Vector<Integer>();
		boolean found;
		int den, num, times = 1, i=0, start, length = 0;
		while(in.hasNextInt()){
			num = in.nextInt();
			den = in.nextInt();
			out.printf("%d/%d = ", num, den);
			ans = new StringBuffer(Integer.toString(num/den));
			ans.append('.');
			found = false;
			start = ans.length();
			don.clear();
			while(!found){
				num = (num%den)*10;
				for(i=0; i<don.size(); i++){
					if(don.get(i)==num){
						found = true;
						break;
					}
				}
				if(found){
					length = don.size() - i;
				}else{
					if(don.size()<50) ans.append(Integer.toString(num/den));
					don.add(num);
				}
			}
			ans.insert(start+i, '(');
			if(don.size()<50)	ans.append(')');
			else	ans.append("...)");
			out.printf("%s\n", ans);
			out.printf("   %d = number of digits in repeating cycle\n\n", length);
		}
	}
}
