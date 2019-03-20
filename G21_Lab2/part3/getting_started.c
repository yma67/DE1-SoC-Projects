int main(){
			int a[5] = {1,20,3,4,97};
			int max_val;
			max_val = 0;
			int i = 0;
			for (i; i < sizeof(a)/sizeof(int);i++){
				if (a[i] > max_val){
					max_val = a[i];				
				}
			}
			return max_val;
}