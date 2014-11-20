/**
* Matrix Operations Class.
* Author: Flávio Freitas Sousa
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
    public:

		/* ==========================================================
                         1. Constructors & Destructors
        ========================================================== */
    	Matrix(unsigned int line_count, unsigned int row_count);        // [1.1] - Constructor
    	Matrix();                                                       // [1.2] - Default Constructor
        ~Matrix();                                                      // [1.3] - Destructor

        /* ==========================================================
                                   2. Set
        ========================================================== */
        void put(double value, unsigned int i, unsigned int j);         // [2.1] - Put (set element)
        void put_next(double value);                                    // [2.2] - Puts value at cursor
        void move_cursor(unsigned int i, unsigned int j);               // [2.3] - Moves cursor to element (i,j)

         /* ==========================================================
                                   3. Get
        ========================================================== */
        unsigned int lines() const;                                     // [3.1] - Line Amount
        unsigned int rows() const;                                      // [3.2] - Row Amount
        double get(unsigned int i, unsigned int j) const;               // [3.3] - Element at position (i,j)

        /* ==========================================================
                           4. Overloaded Operations
        ========================================================== */
              Matrix& operator = (const Matrix);                        // [4.1] - Attribution
        const Matrix  operator + (const Matrix) const;                  // [4.2] - Sum
        const Matrix  operator - (const Matrix) const;                  // [4.3] - Difference
        const Matrix  operator * (const Matrix) const;                  // [4.4] - Product by Matrix
        const Matrix  operator * (const double alpha) const;            // [4.5] - Product by number
        void operator >> (const double& value);                         // [4.6] - Input
        friend std::ostream&                                            // [4.7] - Stream output
            operator << (std::ostream&, const Matrix&);

        /* ==========================================================
                            5. Other Operations
        ========================================================== */
        void resize(unsigned int line_count, unsigned int row_count);   // [5.1] - Resizing
        const Matrix transpose() const;                                 // [5.2] - Returns transpose of this matrix
        const double normalize() const;                                 // [5.3] - Matrix normalization
        const Matrix sub_line(unsigned int i) const;                    // [5.4] - Returns subline
        const Matrix sub_row(unsigned int j) const;                     // [5.5] - Returns subrow
        static const Matrix identity(unsigned int order);               // [5.6] - Returns identity of given order


    private:
        bool valid_bounds(unsigned int i, unsigned int j) const;        // Check bounds
        void pause() const;                                             // Pauses console
        void clear();                                                   // Clears _M

        // Input stream reading this position
        unsigned int
            _line_cursor,
            _row_cursor;

        // Matrix storage
        std::vector< std::vector<double> > _M;
};

#endif // MATRIX_H
