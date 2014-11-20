#include "matrix.h"

#include <iomanip>
#include <cmath>

#define EXCEPTION_BOUNDS "Matrix: Out of bounds"
#define EXCEPTION_ORDER  "Matrix: Incompatible orders"

/* ==========================================================
                1. Constructors & Destructors
========================================================== */
// [1.1] - Constructor
/*+-------------------------------------------------------+
    Matrix mtx (3,5);                                   
                                                        
    // mtx has 3 lines and 4 rows.                      
    // Index starts at 1, not 0.                        
  +-------------------------------------------------------+*/
Matrix::Matrix(unsigned int line_count, unsigned int row_count)
:_line_cursor(1), _row_cursor(1)
{
    this->resize(line_count, row_count);
}


// [1.2] - Empty Constructor
/*+-------------------------------------------------------+
    Matrix mtx;                                         
  +-------------------------------------------------------+*/
Matrix::Matrix()
:_line_cursor(1), _row_cursor(1)
{
    this->resize(1,1);
}


// [1.3] - Destructor
/*+-------------------------------------------------------+
    Matrix *pMtx = new Matrix (10,10);
    (...)                                               
    delete pMtx;
  +-------------------------------------------------------+*/
Matrix::~Matrix()
{
    this->clear();
}

/* ==========================================================
                            2. Set
========================================================== */
// [2.1] - Put (set element)
// If i and j are invalid, nothing happens.
/*+-------------------------------------------------------+
    Matrix mtx (2,3);                                   
                                                        
    // mtx's element at (1,1) receives 8000             
    mtx.put(8000, 1, 1);                                
  +-------------------------------------------------------+*/
void Matrix::put(double value, unsigned int i, unsigned int j)
{
    if (!valid_bounds(i, j))
    {
        std::cout << "Put(" << value << ", " << i << ", " << j << ") failure. Element unchanged." << std::endl;
        std::cout << *this << std::endl;
        std::cout << EXCEPTION_BOUNDS << std::endl;
        pause();
    }
    else
        { _M[i-1][j-1] = value; }
}


// [2.2] - Puts value at cursor 
// Use "[4.6] operator >>" instead of "[2.2] put_next"
//    When the cursor arrives at the end, it goes back to
// the first element: (1,1);
/*+-------------------------------------------------------+
    Matrix mtx (2,2);                                   
    // mtx:                                             
    //  0 0                                             
    //  0 0                                             
                                                        
    mtx.put_next(7);                                    
    // mtx:                                             
    //  7 0                                             
    //  0 0                                             
                                                        
    mtx.put_next(3);                                    
    // mtx:                                             
    //  7 3                                             
    //  0 0                                             
  +-------------------------------------------------------+*/
void Matrix::put_next(double value)
{
    // If cursor position is valid
    if (valid_bounds(_line_cursor, _row_cursor))
    {
        // Puts the new value at that position
        this->put(value, _line_cursor, _row_cursor);

        // Moves the cursor to the right
        _row_cursor++;

        // Row over
        if (_row_cursor > rows())
        {
            // Matrix over -> Back to the first position
            if (_line_cursor == lines())
            {
                _line_cursor = 1;
                _row_cursor = 1;
            }

            // Line over -> Go to next line
            else
            {
                _row_cursor = 1;
                _line_cursor++;
            }
        }
    }
}


// [2.3] - Moves cursor to element (i,j)
// If i and j are invalid, nothing happens.
/*+-------------------------------------------------------+
    Matrix mtx (3,3);                                   
    mtx << 7; // mtx(1,1) contains 7                    
    mtx << 3; // mtx(1,2) contains 3                    
    // mtx:                                             
    //  7 3 0                                           
    //  0 0 0                                           
    //  0 0 0                                           
                                                        
    mtx.move_cursor(3,3);                               
    mtx << 5; // mtx(3,3) contains 5                    
    // mtx:                                             
    //  7 3 0                                           
    //  0 0 0                                           
    //  0 0 5                                           
  +-------------------------------------------------------+*/
void Matrix::move_cursor(unsigned int i, unsigned int j)
{
    if (valid_bounds(i, j))
    {
        _line_cursor = i;
        _row_cursor = j;
    }
}

/* ==========================================================
                            3. Get
========================================================== */
// [3.1] - Line amount
// [3.2] - Row  amount
/*+-------------------------------------------------------+
    Matrix mtx(2,3);                                    
    unsigned int l = mtx.lines(); // l contains 2       
    unsigned int r = mtx.rows();  // r contains 3       
  +-------------------------------------------------------+*/
unsigned int Matrix::lines() const { return _M.size(); }
unsigned int Matrix::rows() const
{
    if (lines() == 0)
        { return 0; }

    return _M.at(0).size();
}


// [3.3] - Element at position (i,j)
// If i and j are invalid, warning and returns 0.
/*+-------------------------------------------------------+
    Matrix mtx(2,2);                                    
    mtx >> 11;                                          
    mtx >> 12;                                          
    mtx >> 21;                                          
    mtx >> 22;                                          
    // mtx:                                             
    //  11 12                                           
    //  21 22                                           
                                                        
    double v = mtx.get(1,2); // v contains 12           
  +-------------------------------------------------------+*/
double Matrix::get(unsigned int i, unsigned int j) const
{
    if (!valid_bounds(i, j))
    {
        std::cout << "Get(" << i << ", " << j << ") failure. Returning 0." << std::endl;
        std::cout << *this << std::endl;
        std::cout << EXCEPTION_BOUNDS << std::endl;
        pause();

        return 0;
    }
    else
        { return _M[i-1][j-1]; }
}

/* ==========================================================
                    4. Overloaded Operations
========================================================== */
// [4.1] - Attribution
/*+-------------------------------------------------------+
    Matrix mtx(2,2);                                    
    mtx >> 11;                                          
    mtx >> 12;                                          
    mtx >> 21;                                          
    mtx >> 22;                                          
    // mtx:                                             
    //  11 12                                           
    //  21 22                                           
                                                        
    // Copy by value:                                   
    Matrix copy;                                        
    copy = mtx;                                         
                                                        
    // copied: elements, cursor, size                   
    //  copy:                                           
    //   11 12                                          
    //   21 22                                          
  +-------------------------------------------------------+*/
Matrix& Matrix::operator=(const Matrix A)
{
    // Protection against self-assignment
    if (this != &A)
    {
        this->resize(A.lines(), A.rows());
        move_cursor(A._line_cursor, A._row_cursor);

        // Assignment of values
        for (unsigned int i = 0; i < this->lines(); i++)
        {
            for (unsigned int j = 0; j < this->rows(); j++)
            {
                this->put(A.get(i+1,j+1), i+1, j+1);
            }
        }
    }
    return *this;
}


// [4.2] - Sum
// If i and j are invalid, warns and throws exception.
/*+-------------------------------------------------------+
    Matrix m1(1,2);                                     
    m1 >> 1;    m1 >> 2;                                
                                                        
    Matrix m2(1,2);                                     
    m2 >> 3;    m2 >> 5;                                
                                                        
    Matrix sum = m1 + m2;                               
    Matrix *sump = new Matrix;                          
    *sump = sum;                                        
                                                        
    std::cout << std::setw(3) << m1 + m2 << std::endl;  
    std::cout << std::setw(3) << sum     << std::endl;  
    std::cout << std::setw(3) << *sump   << std::endl;  
    // Result:                                          
         1   2                                          
      +---+---+                                         
    1 |  4|  7|                                         
      +---+---+                                         
                                                        
         1   2                                          
      +---+---+                                         
    1 |  4|  7|                                         
      +---+---+                                         
                                                        
         1   2                                          
      +---+---+                                         
    1 |  4|  7|                                         
      +---+---+                                         
  +-------------------------------------------------------+*/
const Matrix Matrix::operator+(const Matrix A) const
{
    // In order to sum, the lines and rows must match each other
    if (lines() != A.lines() ||
        rows()  != A.rows())
    {
        std::cout << "Matrix sum failure. Matrix unchanged. Closing." << std::endl;
        std::cout << *this << std::endl;
        std::cout << A << std::endl;
        std::cout << EXCEPTION_ORDER << std::endl;
        pause();
        throw EXCEPTION_ORDER;
    }
    else
    {
        // The result
        Matrix sum (lines(), rows());

        for (unsigned int i = 0; i < sum.lines(); i++)
        {
            for (unsigned int j = 0; j < sum.rows(); j++)
            {
                // Calculating the result values
                double aux = this->get(i+1, j+1) + A.get(i+1,j+1);

                // Assigning to respective positions
                sum.put(aux, i+1, j+1);
            }
        }
        return sum;
    }
}


// [4.3] - Difference
// Details: works the same way as "[4.2] operator+". 
const Matrix Matrix::operator-(const Matrix A) const{
    // In order to sum, the lines and rows must match each other
    if (lines() != A.lines() &&
        rows()  != A.rows())
    {
        std::cout << "Matrix difference failure. Matrix unchanged. Closing." << std::endl;
        std::cout << *this << std::endl;
        std::cout << A << std::endl;
        std::cout << EXCEPTION_ORDER << std::endl;
        pause();
        throw EXCEPTION_ORDER;
    }
    else
    {
        // The result
        Matrix dif (lines(), rows());

        // Calculating the result values
        for (unsigned int i = 0; i < dif.lines(); i++)
        {

            for (unsigned int j = 0; j < dif.rows(); j++)
            {
                // Calculating the result values
                double aux = get(i+1,j+1) - A.get(i+1,j+1);

                // Assigning to respective positions
                dif.put(aux, i+1, j+1);
            }
        }

        return dif;
    }
}


// [4.4] - Product by Matrix
/*+-------------------------------------------------------+
    Matrix m1(2,3);                                     
    m1 >> 1;    m1 >> 2;    m1 >> 3;
    m1 >> 4;    m1 >> 5;    m1 >> 6;
                                                        
    Matrix m2(3,1);                                     
    m2 >> 1;
    m2 >> 2;
    m2 >> 3;
                                                        
    std::cout << std::setw(3) << m1 * m2 << std::endl;  
    
    // Result:                                          
            1
         +---+
       1 | 14|
         +---+
       2 | 32|
         +---+
  +-------------------------------------------------------+*/
const Matrix Matrix::operator*(const Matrix A) const
{
    // In order to multiply, first matrix row count must match second matrix line count
    if (rows() != A.lines())
    {
        std::cout << "Matrix product failure. Matrix unchanged. Closing." << std::endl;
        std::cout << *this << std::endl;
        std::cout << A << std::endl;
        std::cout << EXCEPTION_ORDER << std::endl;
        pause();
        throw EXCEPTION_ORDER;
    }
    else
    {
        // The result
        Matrix product (lines(), A.rows());

        // Calculating the result values
        for (unsigned int i = 0; i < product.lines(); i++)
        {

            for (unsigned int j = 0; j < product.rows(); j++)
            {
                // Calculating the result values
                // P = B*A => P[i][j] = Somatory ( B[i][k] * A[k][j] ), k in [0,  A.lines()]
                double aux = 0;
                for (unsigned int k = 0; k < A.lines(); k++)
                {
                    aux += this->get(i+1, k+1) * A.get(k+1, j+1);
                }

                // Assigning to respective positions
                product.put(aux, i+1, j+1);
            }
        }

        return product;
    }
}





// [4.5] - Product by number (double)
/*+-------------------------------------------------------+
    Matrix m1(2,2);                                     
    m1 >> 2;    m1 >> 1;                                
    m1 >> 1;    m1 >> 2;                                
                                                        
    std::cout << setw(3) << m1 * 4 << std::endl;        
    // Result:                                          
         1   2                                          
      +---+---+                                         
    1 |  8|  4|                                         
      +---+---+                                         
    2 |  4|  8|                                         
      +---+---+                                         
                                                        
    IT IS FORBIDDEN TO WRITE THE NUMBER AT LEFT!        
    Do not do this:  4 * m1;                            
    Only this is allowed: m1 * 4;                       
  +-------------------------------------------------------+*/
const Matrix Matrix::operator*(const double alpha) const
{
    Matrix product (lines(), rows());

    for (unsigned int i = 0; i < lines(); i++)
    {
        for (unsigned int j = 0; j < rows(); j++)
        {
            double aux = this->get(i+1, j+1) * alpha;
            product.put(aux, i+1, j+1);
        }
    }

    return product;
}



// [4.6] - Stream input
/*+-------------------------------------------------------+
    Matrix mtx(2,2);                                    
    mtx >> 11;                                          
    mtx >> 12;                                          
    mtx >> 21;                                          
    mtx >> 22;                                          
                                                        
    // mtx:                                             
    //  11 12                                           
    //  21 22                                           
  +-------------------------------------------------------+*/
void Matrix::operator >> (const double& value)
{
    put_next(value);
}


// [4.7] - Stream output
// Editable with setw(width)
/*+-------------------------------------------------------+
    Matrix mtx (2,2);                                   
    std::cout << std::setw(2) << mtx << std::endl;      
    std::cout << std::setw(6) << mtx << std::endl;      
                                                        
    // Result:                                          
        1  2                                            
      +--+--+                                           
    1 | 0| 0|                                           
      +--+--+                                           
    2 | 0| 0|                                           
      +--+--+                                           
                                                        
            1      2                                    
      +------+------+                                   
    1 |     0|     0|                                   
      +------+------+                                   
    2 |     0|     0|                                   
      +------+------+                                   
  +-------------------------------------------------------+*/
std::ostream& operator << (std::ostream& out, const Matrix& M)
{
    // Retrieving size through std::setw;
    unsigned int width = std::cout.width();
    std::cout << std::setw(0);

    // Size cannot be 0. Default size is 13.
    if (width < 1) { width = 13; }

    // Row Index
    out << "      ";
    for (unsigned int j = 0; j < M.rows(); j++)
    {
        out << std::setw(width) << j+1 << " ";
    }

    // Upper part
    // +------+------+------+
    out << std::endl << "     +";
    for (unsigned int j = 0; j < M.rows(); j++)
    {
        for (unsigned int k = 0; k < width; k++)
        {
            out << "-";
        }
        out << "+";
    }
    out << std::endl;

    // Middle part
    for (unsigned int i = 0; i < M.lines(); i++)
    {
        // Number part
        // |....11|....12|....13|
        out << std::setw(4) << i+1 << " |";
        for (unsigned int j = 0; j < M.rows(); j++)
        {
            out << std::setw(width) << M.get(i+1,j+1) << "|";
        }

        // Lower part (same as upper part)
        out << std::endl << "     +";
        for (unsigned int j = 0; j < M.rows(); j++)
        {
            for (unsigned int k = 0; k < width; k++)
            {
                out << "-";
            }
            out << "+";
        }
        out << std::endl;
    }

    return out;
}


/* ==========================================================
                    5. Other Operations
========================================================== */

// [5.1] Resizing
// If line_count or row_count is 0, does nothing.
/*+-------------------------------------------------------+
    // mtx contains:                                    
    //  11 12                                           
    //  21 22                                           
                                                        
    mtx.resize(3,3);                                    
    // mtx contains:                                    
    //  11 12 0                                         
    //  21 22 0                                         
    //   0  0 0                                         
                                                        
    mtx.resize(1,1);                                    
    // mtx contains:                                    
    //  11                                              
  +-------------------------------------------------------+*/
void Matrix::resize(unsigned int line_count, unsigned int row_count)
{    
    if (line_count != 0 && row_count != 0)
    {
        this->clear();
        _M.resize(line_count);

        for (unsigned int i = 0; i < line_count; i++)
        {
            _M[i].resize(row_count);

            // Default: Zero matrix
            for (unsigned int j = 0; j < row_count; j++)
            {
                _M[i][j] = 0;
            }
        }
    }
}


// [5.2] - Returns transpose of this matrix
/*+-------------------------------------------------------+
    Matrix mtx (3,3);                                   
    m1 >>  11;   m1 >>  12;   m1 >>  13;                
    m1 >>  21;   m1 >>  22;   m1 >>  23;                
    m1 >>  31;   m1 >>  32;   m1 >>  33;                
                                                        
    cout << "m1-t:\n" << setw(3)                        
         << m1.transpose() << endl;                     
                                                        
    // Result                                           
         1   2   3                                      
      +---+---+---+                                     
    1 | 11| 21| 31|                                     
      +---+---+---+                                     
    2 | 12| 22| 32|                                     
      +---+---+---+                                     
    3 | 13| 23| 33|                                     
      +---+---+---+                                     
                                                        
  +-------------------------------------------------------+*/
const Matrix Matrix::transpose() const
{
    Matrix T (rows(), lines());
    for (unsigned int i = 0; i < lines(); i++)
    {
        for (unsigned int j = 0; j < rows(); j++)
        {
            double aux = this->get(i+1, j+1);
            T.put(aux, j+1, i+1);
        }
    }
    return T;
}

// [5.3] - Normalization
const double Matrix::normalize() const
{
    double aux = 0;
    for (unsigned int i = 0; i < lines(); i++)
    {
        for (unsigned int j = 0; j < rows(); j++)
        {
            aux += pow(this->get(i+1, j+1), 2);
        }
    }
    return sqrt(aux);
}

// [5.4] - Subline
const Matrix Matrix::sub_line(unsigned int i) const
{
    if (i > lines())
    {
        std::cout << EXCEPTION_BOUNDS << std::endl;
        throw        EXCEPTION_BOUNDS;
    }

    Matrix L (1, rows());

    for (unsigned int j = 1; j <= rows(); j++)
    {
        double element = this->get(i, j);
        L.put(element, 1, j);
    }

    return L;
}

// [5.5] - Subrow
const Matrix Matrix::sub_row(unsigned int j) const
{
    if (j > rows())
    {
        std::cout << EXCEPTION_BOUNDS << std::endl;
        throw        EXCEPTION_BOUNDS;
    }

    Matrix R (lines(), 1);

    for (unsigned int i = 1; i <= rows(); i++)
    {
        double element = this->get(i, j);
        R.put(element, i, 1);
    }

    return R;
}

// [5.6] - Identity
const Matrix Matrix::identity(unsigned int order)
{
    // Validity check
    if (order == 0)
        { return Matrix::identity(1); }

    Matrix I (order, order);
    for (unsigned int i = 1; i <= order; i++)
    {
        for (unsigned int j = 1; j <= order; j++)
        {
            if (i == j)
                { I.put(1, i, j); }
            
            else
                { I.put(0, i, j); }
        }
    }

    return I;
}


/* ==========================================================
                           Private
========================================================== */
// Verifies if the given bounds are valid
/*+-------------------------------------------------------+
    Matrix mtx (2,3);                                   
                                                        
    mtx.valid_bounds(3,2);  // Returns false            
    mtx.valid_bounds(0,2);  // Returns false            
    mtx.valid_bounds(1,1);  // Returns true             
    mtx.valid_bounds(2,3);  // Returns true             
  +-------------------------------------------------------+*/
bool Matrix::valid_bounds(unsigned int i, unsigned int j) const
{
    if (i == 0 || i > lines() ||
        j == 0 || j > rows())
        return false;

    return true;
}

// Pauses console
void Matrix::pause() const
{
    std::cout << "\nSystem paused. Press Enter to proceed..." << std::endl;
    std::cin.get();
}

// Clears _M
void Matrix::clear()
{
    // Clears each line
    for (std::vector< std::vector<double> >::iterator it = _M.begin(); it != _M.end(); it++)
    {
        it->clear();
    }

    // Clears Matrix
    _M.clear();

    // Reset cursor to element (1,1)
    move_cursor(1,1);
}
