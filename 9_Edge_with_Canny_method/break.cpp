#include <iostream>

using namespace std;

int main(){

	int c=0, m=0;

	for (int i=1; i<100; i++){
		if ( i%2 == 0 ){
			m = i;
			cout<<"m -> "<<m<<"\t";
	
			if ( m == 20 )
				break;
		}
		
		cout<<"i -> "<<i<<"\t";
	}

	cout<<endl<<endl;
	return 0;
}
