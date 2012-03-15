#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

template <class elem_t>
class Matrix {
    typedef unsigned char                                 width_t;                   //Max 255x255
    typedef std::vector<std::vector<elem_t> >             matrix_vect_t;             //A vector containing the indices of
    typedef std::vector<elem_t>                           col_vect_t;             //A vector containing the indices of

    matrix_vect_t    m_matrix;

    public:
        //Default constructor
        Matrix( width_t rows, width_t cols, elem_t val = 0 ) :
            m_matrix(rows, col_vect_t(cols, val))
        {

            //if()
        }

        bool canMultiply(const Matrix<elem_t>& matrix )const{
            if(cols() == matrix.rows()) return true;
            return false;
        }

        bool canAdd(const Matrix<elem_t>& matrix )const{
            if(rows() == matrix.rows() && cols() == matrix.cols()) return true;
            return false;
        }

        inline bool isSquare()const{
            return (rows() == cols());
        }

        width_t size()const{
            if(isSquare()){
                return rows();
            }else{
                return 0;
            }
        }

        inline width_t rows()const{
            return m_matrix.size();
        }

        inline width_t cols()const{
            return m_matrix[0].size();
        }

        inline void debug_output()const{
            std::cout << "Matrix is " << (int)rows() << "x" << (int)cols() << std::endl;
        }
};

#endif //MATRIX_H
