template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m) // Matrix of n rows and m cols
    {
        A.assign(n, vector<T>(m));
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; } // To get access without dot

    static Matrix Identity(lli n) // Identity Matrix<T>::Identity(rows)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }

    //* /////////////////// Operators ////////////////////////

    Matrix operator*(lli k) const{
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = k*A[i][j];
        return C;
    }
    
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] += + (A[i][k]*B[k][j]);

        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        Matrix<T> aux = *this;
        while(e)
        {
            if(e&1) res = res*aux;
            e>>=1;
            aux = aux*aux;
        }
        return res;
    }

    Matrix operator+(const Matrix &B) const{
        assert(rows == B.rows && cols == B.cols);
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    //* ///////////// Gauss-Jordan ///////////////////

    void swapRows(lli i, lli j){ swap(A[i], A[j]); }

    void addRow(lli row1, lli row2, T c)
    {
        for(int j = 0; j<cols; j++) A[row1][j] += ( c * A[row2][j] );
    }

    void scaleRow(lli row, ld k)
    {
        for(int j = 0; j<cols; j++) A[row][j] *= k;
    }

    T inverseMult(T k) {
        return 1 / k;
        // return powerMod(k, MOD-2, MOD);
    }

    T inverseSum(T k) {
        return -k;
        // return (MOD-k % MOD) % MOD;
    }


    void GaussJordan(bool SLE = false, Matrix< T > &ans = NULL) // if inverse, ans = Identity
    {
        for(int row = 0, col = 0; row < rows && col < cols; col++)
        {
            if(A[row][col] == 0)
            {
                int pivot = row;
                for(int i = row + 1; i<rows; i++ ){
                    if( abs( A[i][col] > abs(A[pivot][col]) ) ){ //* Selecciona la Pivot como el numero mas grande (Heuristico)
                        pivot = i;
                    }
                }
                if( abs( A[pivot][col] ) > 0  ){ //* Si el numero mas grande no es cero, swapea las dos filas
                    swapRows(pivot,row);  
                    if(SLE) ans.swapRows(pivot, row);
                } 
                else continue;
            }

            //* Re-escalea la fila, para que el pivote sea 1.
            T invMult = inverseMult(A[row][row]);
            scaleRow(row, invMult);
            if(SLE){
                ans.scaleRow(row, invMult);
            } 


            for(int i = 0; i<rows; i++) //* Se realizan combinaciones lineales para que los otros numeros sean 0 excepto el pivote
            {
                if(i != row && A[i][col] != 0) //* No se agrega a el mismo ni cuando es 0 ya
                {
                    T invSum = inverseSum(A[i][col]);
                    addRow(i, row, invSum);
                    if(SLE) ans.addRow(i, row, invSum);
                }
            }
            row++;
        }
    }

    //* //////////////////////////////////////////////
    void printMatrix()
    {
        for(int i = 0; i<rows; i++)
        {
            cout<<"|";
            for(int j = 0; j<cols; j++)
            {
                cout<<A[i][j]<< (j!=cols-1? " ": "");
            }
            cout<<"|\n";
        }
        cout << endl;
    } 
};

//O(n^3 log(k)^2)
template <typename T>
Matrix<T> geometric(const Matrix<T> &M, int k) //A + A^2 + ... + A^(2*n) = (A+A^2+..+A^(n)) * (I + A^(n))
{  //!Warning if k == 0 will get in cycle
    int n = M.rows;
    auto I = Matrix<T>::Identity(n);
    if(k == 1){
        return M;
    }
    else
    {
        int mid = k/2;
        auto ans = geometric(M, mid) * (I + (M^mid));
        if(k&1) return ans + (M^k);
        else return ans;
    }
}

