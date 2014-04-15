class _Matrix{
public:
	typedef LL Type;
	Type buffer[MAXN][MAXN];

	struct Matrix{
		Type x[MAXN][MAXN];
		int n;
		Matrix(int n){this->n = n;}
		void mul(Matrix &m){
			double tot = 0;
			tot = 0;
			for(int i = 0;i<n;i++){
				for(int j = 0;j<n;j++){
					buffer[i][j] = 0;
					for(int k = 0;k<n;k++){
						buffer[i][j]+=x[i][k]*m.x[k][j];
					}
				}
			}
			for(int i = 0;i<n;i++)
				for(int j = 0;j<n;j++) x[i][j] = buffer[i][j];
		}

		void print(){
			for(int i = 0;i<n;i++){
				for(int j = 0;j<n;j++) cout<<x[i][j]<<" ";
				cout<<endl;
			}
		}

		void init(){
			for(int i = 0;i<n;i++)
				for(int j = 0;j<n;j++) x[i][j] = 0;
			for(int i = 0;i<n;i++) x[i][i] = 1;
		}
	};

	Matrix Pow(Matrix &x,LL p){
		Matrix m;
		m.init();
		while(p){
			if(p&1){
				m.mul(x);
			}
			x.mul(x);
			p>>=1;
		}
		return m;
	}
} matrix;
