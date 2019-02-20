extern	int	MAX_2(int x, int y);

int main(){
		int a[6] = {55,32,2,6,8,76};
		int max_val = 0;
		int i = 0;
		for (i; i < sizeof(a)/sizeof(int);i++){
			max_val = MAX_2(max_val,a[i]);
		}
		return max_val;
}