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
        {}

        Matrix(const Matrix& cpy):
            m_matrix(cpy.rows(), col_vect_t(cpy.cols(), 0))
        {
            for(int r = 0; r < cpy.rows(); r++){
                for(int c = 0; c < cpy.cols(); c++){
                    set(r, c, cpy.get(r, c));
                }
            }
        }

        Matrix<elem_t>& operator*(const Matrix<elem_t>& matrix) const {
            if(canMultiply(matrix)){
                Matrix<elem_t> result(rows(), matrix.cols());
                elem_t sum;

                for(int row  = 0; row < rows(); row++){
                    for(int mcol = 0; mcol < matrix.cols(); mcol++){
                        sum = 0;
                        for(int mrow = 0; mcol < matrix.rows(); mrow++){
                            sum += matrix.get(mrow, mcol) * get(row, mrow);
                        }
                        std::cout << "Set results\n";
                        result.set(row, mcol, sum);
                    }
                }

                return result;
            }

            throw(0);
        }

        elem_t get(width_t row, width_t col)const{
            if(row+1 > rows() || col+1 > cols() ){
                std::cout << "[Matrix][get " << (int)row << ", " << (int)col << "] Index is out of bounds\n";
                return 0;
            }
            std::cout << "Get " << (int)row << ", " << (int)col << " from ";
            debug_output();
            return m_matrix[row][col];
        }

        void set(width_t row, width_t col, elem_t val){
            std::cout << "Can multiply\n";
            m_matrix[row][col] = val;
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
