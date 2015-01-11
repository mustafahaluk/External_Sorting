#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 100000000
string j;


int xx=800;// the number of doubles a temp file initialy gets
int b;//the number of doubles that last temp file has after division 
double m;
int n;//the number of temp files initially
int num=0;//given number at the beginning of input

//Merges two temp files into a temp file, Writes on first one and Deletes second
void merge(int a1,int a2,int a3){ 
	double c1,c2;
	ifstream read1("/tmp/in" + to_string(a1) );
	ifstream read2("/tmp/in" + to_string(a2) );
	ofstream write("/tmp/intemp");
	read1>>c1;
	read2>>c2;
	double l1=c1;
	double l2=c2;
	while(read1.good() and read2.good()){
		if((c1<c2) ){
			write<<fixed<<setprecision(6)<<c1<<endl;
			read1>>c1;
			if(l1==c1){c1=10000000.0;}
			else{l1=c1;}
			cout<<"O";
		}
		else {
			write<<fixed<<setprecision(6)<<c2<<endl;
			read2>>c2;
			if(l2==c2){c2=10000000.0;}
			else{l2=c2;}
			cout<<"K";
		}
	}
	
	while(read1.good()){
		if(c1>c2) {write<<fixed<<setprecision(6)<<c2<<endl; c2=10000000.0;}
		write<<fixed<<setprecision(6)<<c1<<endl;
		read1>>c1;
		if(l1==c1){c1=10000000.0;}
		else{l1=c1;}
		
	}
	while(read2.good()){
		if(c1<c2){ write<<fixed<<setprecision(6)<<c1<<endl; c1=10000000.0;}
		write<<fixed<<setprecision(6)<<c2<<endl;
		read2>>c2;
		if(l2==c2){c2=10000000.0;}
		else{l2=c2;}
		
	}
	
	remove(("/tmp/in"+to_string(a1)).c_str());
	remove(("/tmp/in"+to_string(a2)).c_str());
	rename(("/tmp/intemp"),("/tmp/in"+to_string(a3)).c_str());
	
}
int main(int argc, char *argv[]){
	ifstream fin;//for reading
	fin.open(argv[1]);
	if(fin.is_open()){
		fin>>num;
		b= num-(num/xx)*xx;
		if(b==0)n=num/xx;
		else n=num/xx+1;
		double arr1[xx];
		for(int i=0; i<num/xx; i++){//main
			for(int k=0; k<xx; k++){
				fin>>arr1[k];
			}
			make_heap(arr1,arr1+xx);
			for(int k=0; k<xx; k++){//Makes array sorted
				double temmp= arr1[0];
				arr1[0]=arr1[xx-k-1];
				arr1[xx-k-1]=temmp;
				make_heap(arr1,arr1+(xx-k-1));
			}
			ofstream fout;
			j = "/tmp/in"+to_string(i+1);
			fout.open(j);
			for(int i=0;i<xx;i++){//Writes to the temp files
				double m=arr1[i];
				fout<<fixed<<setprecision(6)<<m<<endl;
			}
			fout.close();
		}
		if(b>0){//Makes same thing above for the input that reminds after division
			for(int k=0; k<b; k++){
				fin>>m;
				arr1[k]=m;
			}
				for(int k=0; k<b; k++){
				double temmp= arr1[0];
				arr1[0]=arr1[b-k-1];
				arr1[b-k-1]=temmp;
				make_heap(arr1,arr1+(b-k-1));
			}	
			ofstream fout;
			j = "/tmp/in"+to_string(num/xx+1);
			fout.open(j);
			for(int i=0;i<b;i++){
				double m=arr1[i];
				fout<<fixed<<setprecision(6)<<m<<endl;
			}
			fout.close();
		}
	}
	fin.close();
	
	while(true){//Merges all temp files until there is one file that is the sort of input
		if(n==1){
			//
			break;
		}
		if(n%2==1){
			merge(n-1,n,n-1);
			n--;
		}
		
		for(int i=1; i<=n/2; i++) {
			merge(2*i-1,2*i,i);
		}
		n=n/2;
	}
	double theEnd;
	ifstream fina("/tmp/in1" );
	ofstream fout;
	fout.open(argv[2]);
	fout.unsetf(ios::floatfield);
	fout.precision(6);
	fout.setf(ios::fixed, ios::floatfield);
	for(int i=0;i<num;i++){//Takes the last temp files after merging and Writes it to the output
		fina>>theEnd;
		fout<<theEnd<<endl;
	}
	remove(("/tmp/in"+to_string(1)).c_str());//Removes the last temp files from hard disk
	return 0;
}

