#include<iostream>
#include<cmath>
using namespace std;

class Matrix
{
	int height;
	int width;
	long long** matrix; // matrix
	long long* ext;//extended column
	long long sign(long long x)
	{
		return x > 0 ? 1 : x == 0 ? 0 : -1;
	}
	long long GCD(unsigned long long a, unsigned long long b)// greatest common divisor
	{
		if(a < b) swap(a, b);
		while(b)
		{
			a %= b;
			swap(a, b);
		}
		return a;
	}
	#define LCM(a, b) a * b / GCD(a, b)//least common multiply
	long long calculateDet(long long** matrix, int l, int u)
	{
		if (u - l <= 2)
		{
			if (u - l == 2)
				return matrix[l][l] * matrix[u - 1][u - 1] - matrix[u - 1][l] * matrix[l][u - 1];
			if (u - l == 1)
				return matrix[l][l];
			return 0;
		}
		long long s = 0;
		for(int col = l; col < u; col++)
			if ((l + col) % 2 == 0)
				s += matrix[l][col] * calculateDet(matrix, l + 1, u);
			else
				s -= matrix[l][col] * calculateDet(matrix, l + 1, u);
		return s;
	}
	void spaces(uint a)
	{
		for(int i = 0; i < a; i++)
			cout << ' ';
	}
	int numerals(long long x)
	{
		if (x == 0) return 0;
		x = abs(x);
		int n = 1;
		int p = 1;
		while (x > p)
		{
			p *= 10;
			n++;
		}
		if (x < p) n--;
		return n;
	}
	Matrix(int height, int width)
	{
		ext = 0;
		this->height = height;
		this->width = width;
		matrix = new long long*[height];
		for (int i = 0; i < height; i++)
			matrix[i] = new long long[width];
		for (int i = 0;i < height;i++)
			for (int j = 0;j < width;j++)
				matrix[i][j] = 0;
	}
public:
	Matrix(const Matrix& other)
	{
		height = other.height;
		width = other.width;
		matrix = new long long*[height];
		for (int i = 0; i < height; i++)
			matrix[i] = new long long[width];
		for (int i = 0; i < height; i++)
			for(int j = 0;j < width; j++)
				matrix[i][j] = other.matrix[i][j];
		if (other.ext)
		{
			ext = new long long[height];
			for (int i = 0; i < height; i++)
				ext[i] = other.ext[i];
		} else ext = 0;
	}
	Matrix(long long** b, int height, int width)
	{
		ext = 0;
		this->height = height;
		this->width = width;
		matrix = new long long*[height];
		for (int i=0; i<height; i++)
			matrix[i] = new long long[width];
		for (int i=0; i<height; i++)
			for (int j=0; j<width; j++)
				matrix[i][j] = b[i][j];
	}
	Matrix(long long** b, int height, int width, long long* fr)
	{
		this->height = height;
		this->width = width;
		matrix = new long long*[height];
		for (int i=0; i<height; i++)
			matrix[i] = new long long[width];
		for (int i=0; i<height; i++)
			for (int j=0; j<width; j++)
				matrix[i][j] = b[i][j];
		ext = new long long[height];
		for (int i=0; i<height; i++)
			ext[i] = fr[i];
	}
	void appExt(long long* fr)
	{
		if (ext)
		{
			cout << "You tried to replace an old extended matrix" << endl;
			exit(0);
		}
		ext = new long long[height];
		for (int i = 0; i < height; i++)
			ext[i] = fr[i];	
	}
	~Matrix()
	{
		for (int i = 0; i < height; i++)
			delete[] matrix[i];
		delete[] matrix;
		if (ext) delete[] ext;
	}
	int size1(){ return height; }
	int size2(){ return width; }
	long long* operator[](const int i)
	{
		return matrix[i];
	}
	Matrix& operator=(const Matrix& other)
	{
		for (int i = 0; i < height; i++)
			delete[] matrix[i];
		delete[] matrix;
		height = other.height;
		width = other.width;
		matrix = new long long*[height];
		for (int i = 0;i < height; i++)
			matrix[i] = new long long[width];
		for (int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				matrix[i][j] = other.matrix[i][j];
		return *this;
	}
	friend bool operator==(const Matrix& l, const Matrix& r);
	friend bool operator!=(const Matrix& l, const Matrix& r);
	friend Matrix operator*(const long long& x, const Matrix& other);
	friend Matrix operator*(const Matrix& other, const long long& x);
	friend Matrix operator+(const Matrix& l, const Matrix& r);
	friend Matrix operator-(const Matrix& r);
	friend Matrix operator-(const Matrix& l, const Matrix& r);
	friend Matrix operator*(const Matrix& l, const Matrix& r);
	Matrix& operator*=(const Matrix& other){
		*this = operator*(*this, other);
		return *this;
	}
	Matrix& operator+=(const Matrix& other){
		*this = operator+(*this, other);
		return *this;
	}
	void print(){
		for (int i=0;i<height;i++){
			for (int j=0;j<width;j++)
				cout<<matrix[i][j]<<' ';
			cout<<endl;
		}
		cout<<endl;
	}
	void printFormat(){
		int maxNumberOfNumeral = 0;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int n = numerals(matrix[i][j]);
				if (matrix[i][j] < 0) n++;
				if (n > maxNumberOfNumeral)
					maxNumberOfNumeral = n;
			}
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++)
			{
				cout<<matrix[i][j];
				if(matrix[i][j] < 0)
					spaces(maxNumberOfNumeral - numerals(matrix[i][j]));
				else spaces(maxNumberOfNumeral - numerals(matrix[i][j]) + 1);

			}
			if (ext)
				cout << " | " << ext[i];
			cout << endl;
		}
		cout<<endl;
	}
	void sumStr(int s1, int s2){
		for (int i = 0; i < width; i++)
			matrix[s1][i] += matrix[s2][i];
	}
	void sumStr(int s1,int k1, int s2, int k2){
		for (int i = 0;i < width; i++)
			matrix[s1][i] = k1 * matrix[s1][i] + k2 * matrix[s2][i];
	}
	void swapStr(int s1, int s2){
		for (int i = 0;i < width; i++)
			swap(matrix[s1][i], matrix[s2][i]);
	}
	void multyplyStrbyNumber(int k,int s)
	{
		for (int i = 0; i < width; i++)
			matrix[s][i] = k * matrix[s][i];
	}
	/*void GetLowerTriangleView(){
		
	}*/
	void getUpperTriangleView()
	{
		int lowerLimit1 = 0;
		int lowerLimit2 = 0;
		while(lowerLimit1 != height && lowerLimit2 != width)
		{
			int i = lowerLimit1;
			while (matrix[i][lowerLimit2] == 0)
				if (i < height - 1)
					i++;
				else
				{
					i = lowerLimit1;
					if (lowerLimit2 < width - 1)
						lowerLimit2++;
					else return;
				}
			if (i > lowerLimit1)
				swapStr(lowerLimit1, i);
			for (int str = lowerLimit1 + 1; str < height; str++)
			{
				if(matrix[str][lowerLimit2] == 0) continue;
				long long lcm = LCM(abs(matrix[lowerLimit1][lowerLimit2]), abs(matrix[str][lowerLimit2]));
				long long k1 = lcm / abs(matrix[lowerLimit1][lowerLimit2]) * sign(matrix[lowerLimit1][lowerLimit2]) * sign(matrix[str][lowerLimit2]);
				long long k2 = lcm / abs(matrix[str][lowerLimit2]);
				multyplyStrbyNumber(k2, str);
				for (int col = lowerLimit2; col < width; col++)
					matrix[str][col] -= k1 * matrix[lowerLimit1][col];
				if (ext)
					ext[str] -= k1 * ext[lowerLimit1];
			}
			lowerLimit1++;
		}
	}
	long long multiplyDiagonalElements()
	{
		if (height != width)
		{
			cout << "The matrix has not a square form" << endl;
			exit(0);
		}
		long long m = 1;
		for (int i = 0; i < height; i++)
			m *= matrix[i][i];
		return m;
	}
	long long det()
	{
		if (height != width)
		{
			cout << "The matrix has not a square form" << endl;
			exit(0);
		}
		getUpperTriangleView();
		return multiplyDiagonalElements();
	}
	long long det1()
	{
		if (height != width)
		{
			cout << "Error! The matrix has not a square form" << endl;
			exit(0);
		}
		return calculateDet(matrix, 0, height);
	}
	double* solve()
	{
		if (!ext || height != width)
		{
			cout << "The system can't be solved by a Cramer's rule" << endl;
			exit(0);
		}
		double d;
		{
			Matrix m(height, width);
			for (int str = 0; str < height; str++)
				for (int col = 0; col < width; col++)
					m[str][col] = matrix[str][col];
			d = m.det();
		}
		double* ans = new double[width];
		for (int i = 0; i < width; ++i)
		{
			Matrix mi(height, width);
			for (int str = 0; str < height; str++)
				for (int col = 0; col < width; col++)
					if (col == i)
						mi[str][col] = ext[str];
					else mi[str][col] = matrix[str][col];
			ans[i] = mi.det() / d;
		}
		return ans;
	}
	void set( int i, int j, long long x){
		matrix[i][j] = x;	
	}
	long long get(int i, int j){
		return matrix[i][j];
	}
	long long getExt(int i)
	{
		if(!ext)
		{
			cout << "An extended matrix doesn't exist" << endl;
			exit(0);
		}
		return ext[i];
	}
	void setExt(int i, long long x)
	{
		if (!ext)
		{
			cout << "An extended matrix doesn't exist" << endl;
			exit(0);
		}
		ext[i] = x;
	}
	void T(){
		for (int i = 0; i < height; i++)
			for (int j = i + 1; j < width; j++)
				if (i!=j)
					swap(matrix[i][j], matrix[j][i]);
	}
};
Matrix operator*(const long long& x,const Matrix& other)
{
		Matrix M(other.height,other.width);
		for (int i = 0;i < other.height; i++)
			for(int j =0;j < other.width; j++)
				M.matrix[i][j] = other.matrix[i][j] * x;
		return M;
}
Matrix operator*(const Matrix& other, const long long& x)
{
		return operator*(x,other);
}
Matrix operator+(const Matrix& l,const Matrix& r)
{
	if (l.height==r.height && l.width==r.width)
	{
		Matrix M(l.height,l.width);
		for (int i = 0;i < l.height; i++)
			for (int j = 0;j < l.width; j++)
				M.matrix[i][j]=l.matrix[i][j]+r.matrix[i][j];
		return M;
	} else
	{
		cout << "Error! There are different sizes!" << endl;
		int sizem1;
		int sizem2;
		if(l.height >= r.height) sizem1 = l.height;
		else sizem1 = r.height;
		if(l.width >= r.width) sizem2 = l.width;
		else sizem2 = r.width;
		Matrix M(sizem1, sizem2);
		return M;
	}
}
Matrix operator*(const Matrix& l,const Matrix& r)
{
	if (l.height == r.width && l.width == r.height)
	{
		Matrix M(l.height, l.width);
		for (int i = 0; i < l.height; i++)
			for (int j = 0; j < l.width; j++)
				for (int k = 0; k < l.width; k++)
						M.matrix[i][j] += l.matrix[i][k] * r.matrix[k][j];
		return M;
	} else
	{
		cout << "Error! There are different sizes!" << endl;
		int sizem1;
		int sizem2;
		if(l.height >= r.height) sizem1 = l.height;
		else sizem1 = r.height;
		if (l.width >= r.width) sizem2 = l.width;
		else sizem2 = r.width;
		Matrix M(sizem1, sizem2);
		return M;
	}
}

bool operator==(const Matrix& l,const Matrix& r)
{
	if (l.height == r.height && l.width == r.width)
	{
		for (int i = 0; i < l.height; i++)
			for (int j = 0; j < l.width; j++)
				if (l.matrix[i][j] != r.matrix[i][j]) return false;
		return true;
	}
	return false;
}
bool operator!=(const Matrix& l,const Matrix& r)
{
	return !operator==(l,r);
}
Matrix operator-(const Matrix& r)
{
	Matrix matrix(r);
	for (int i = 0; i < matrix.size1(); ++i)
		for (int j = 0; j < matrix.size2(); ++j)
			matrix[i][j] = -matrix[i][j];
	return matrix;
}
Matrix operator-(const Matrix& l, const Matrix& r)
{
	return operator+(l, -r);
}