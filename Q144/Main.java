import java.io.*;
import java.util.*;

class Student{
	public int rank, money;
	
	Student(){
		rank = 0;
		money = 0;
	}

	Student(int a, int b){
		rank = a;
		money = b;
	}
}

class Machine{
	public int money, level, limit;

	Machine(){
		money = 0;
		level = 0;
	}
}

public class Main{
	public static void main(String argv[]){
		Scanner in = new Scanner( System.in );
		PrintWriter out = new PrintWriter(System.out, true);
		Queue<Student> wait_line = new LinkedList<Student>();
		Student stu;
		Machine mac = new Machine();
		int n, k, i;
		while(in.hasNextInt()){
			n = in.nextInt();
			k = in.nextInt();
			if(n==0&&k==0)	break;
			/*
				Setting
			*/
			for(i=1; i<=n; i++){
				wait_line.add(new Student(i, 0));
			}
			mac.money = 1;
			mac.level = 1;
			/*
				Run Simulation
			*/
			while(!wait_line.isEmpty()){
				stu = wait_line.remove();
				if(stu.money+mac.money>40){
					mac.money = stu.money + mac.money - 40;
					stu.money = 40;
				}else{
					stu.money += mac.money;
					if(mac.level==k){
						mac.level = 1;
						mac.money = 1;
					}else{
						mac.money = ++mac.level;
					}
				}
				if(stu.money==40){
					out.printf("%3d", stu.rank);
				}else{
					wait_line.add(stu);
				}
			}
			out.printf("\n");
		}
	}
}
