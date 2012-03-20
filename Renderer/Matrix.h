#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

typedef float                                    angle_t; //Radians
typedef unsigned char                                 width_t;                   //Max 255x255

template <class elem_t>
class Matrix {

    //
    /// Type definitions
    typedef std::vector<std::vector<elem_t> >             matrix_vect_t;             //A vector containing the indices of
    typedef std::vector<elem_t>                           col_vect_t;             //A vector containing the indices of

    //
    ///Private member variables
    matrix_vect_t    m_matrix;

    public:

    static bool MatrixIsVector(const Matrix& matrix){
        if(matrix.rows() == 4 && matrix.cols() == 1){
            if(matrix.get(3, 0) == 0){
                return true;
            }
        }

        return false;
    }

    static bool MatrixIsPoint(const Matrix& matrix){
        if(matrix.rows() == 4 && matrix.cols() == 1){
            if(matrix.get(3, 0) == 1){
                return true;
            }
        }

        return false;
    }

    static Matrix<elem_t> CreateIdentity(const Matrix& a){
        elem_t val;
        for(width_t row = 0; row < a.rows(); row++ ){
            for(width_t col= 0; col < a.cols(); col++ ){
                if(row == col){
                    val = 1;
                }else{
                    val = 0;
                }

                a.set(val, row, col);
            }
        }
    }

    static Matrix<elem_t> Inverse(const Matrix& a){ //should not be static
        Matrix<elem_t> result = a;

        if(a.isSquare()){
            if(a.determinant() != 0){
                std::cout << "Cofactor: \n";
                Matrix<elem_t> cfm = CofactorMatrix(a);
                cfm.debug_output();
                std::cout << "Transpose\n";
                Matrix<elem_t> adj = Transpose(cfm);
                adj.debug_output();
                std::cout << "Result\n";
                result = adj * (1/a.determinant());
                result.debug_output();
            }
        }

        return result;
    }

    static Matrix<elem_t> CofactorMatrix(const Matrix& a){
        Matrix<elem_t> result(a.rows(), a.cols());

        signed char m = 1;

        if(a.isSquare()){
            for(width_t r = 0; r < a.rows(); r++){
                for(width_t c = 0; c < a.cols(); c++){
                    result.set((m * a.cofactor(r, c), r, c ));
                    m *= -1;
                }
            }
        }

        return result;
    }

    static Matrix<elem_t> Transpose(const Matrix& a){
        Matrix<elem_t> result(a.cols(), a.rows());

        for(width_t r =0; r < a.rows(); r++){
            for(width_t c = 0; c < a.cols(); c++){
                result.set(a.get(r, c), c, r);
            }
        }

        return result;
    }

    /*
    //Not complete
    static Matrix<elem_t> Augment(const Matrix& a, const Matrix& b) {//should not be static
        Matrix<elem_t> result = a;

        if(a.isSquare() && b.isSquare())
        {
            if(a.rows() == b.rows())
            {
                a.m_matrix.reserve(a.rows());
                b.m_matrix.reserve(b.rows());
            }
        }
    }
    */

    static Matrix CreateRotationMatrix(const Matrix& rotation){

        std::cout << "[Matrix] Creating Rotation Matrix r: \n";
        rotation.debug_output();

        Matrix result(4, 4, 0);

        if(!MatrixIsVector(rotation)){
            std::cout << "Not a vector\n";
            return result;
        }


        elem_t x_rot = rotation.get(0, 0);
        elem_t y_rot = rotation.get(1, 0);
        elem_t z_rot = rotation.get(2, 0);

        result.set( cos(y_rot)*cos(z_rot),                                              0,   0 );
        result.set( cos(z_rot)*sin(x_rot)*sin(y_rot) - cos(x_rot)*sin(y_rot),           0,   1 );
        result.set( cos(x_rot)*sin(z_rot)*sin(y_rot) + cos(x_rot)*sin(y_rot),           0,   2 );
        result.set( cos(y_rot)*sin(z_rot),                                              1,   0 );
        result.set( cos(x_rot)*sin(z_rot) + sin(x_rot) * sin(y_rot) * sin(z_rot),       1,   1 );
        result.set( (-1*cos(z_rot))*sin(x_rot) + cos(x_rot) * sin(y_rot) * sin(z_rot),  1,   2 );
        result.set( -1*sin(y_rot),                                                      2,   0 );
        result.set( cos(y_rot) * sin(x_rot),                                            2,   1 );
        result.set( cos(y_rot) * sin(z_rot),                                            2,   2 );
        result.set( 1,                                                                  3,   3 );


        /*if(axis.get(0, 0) == 1){        //x-axis
            result.set(0, 0, 1);
            result.set(1, 1, cos(angle));
            result.set(1, 2, sin(angle));
            result.set(2, 1, -1*sin(angle));
            result.set(2, 2, cos(angle));
        }else if(axis.get(1, 0) == 1){   //y-axis
            result.set(0, 0, cos(angle));
            result.set(0, 2, -1*sin(angle));
            result.set(1, 1, 1);
            result.set(2, 0, sin(angle));
            result.set(2, 2, cos(angle));
        }else if(axis.get(2, 0)){
            result.set(0, 0, cos(angle));
            result.set(0, 1, sin(angle));
            result.set(1, 0, -1*sin(angle));
            result.set(1, 1, cos(angle));
            result.set(2, 2, 1);
        }*/

        result.set(3, 3, 1);
        return result;
    }

    //Default constructor
    Matrix( width_t rows, width_t cols, elem_t val = 0 ) :
        m_matrix(rows, col_vect_t(cols, val))
    {}

    Matrix(const Matrix& cpy):
        m_matrix(cpy.rows(), col_vect_t(cpy.cols(), 0))
    {
        for(int r = 0; r < cpy.rows(); r++){
            for(int c = 0; c < cpy.cols(); c++){
                set(cpy.get(r, c), r, c);
            }
        }
    }

    elem_t determinant() const{ //Only works on 3x3
        elem_t          dval = 0;

        if(isSquare())
        {
            elem_t          tmpval;
            width_t         pos;
            if(rows() == 2)
            {
                dval = (get(0, 0) * get(1, 1)) - (get(0, 1) * get(1, 0));
            }else{

                signed char m = 1;

                for(width_t r = 0; r < rows(); r++){
                    //for(width_t c = 0; c < cols(); c++){
                        dval += m*(get(r, 0) * cofactor(r, 0));
                        m *= -1;
                    //}
                }
            }
        }


        return dval;
    }

    elem_t cofactor(width_t xrow, width_t xcol) const{
        elem_t cof = 0;

        if(!outOfBounds(xrow, xcol) && isSquare()){
            width_t currow = 0;
            width_t curcol = 0;

            Matrix<elem_t> result(rows()-1, cols()-1);

            for(width_t r = 0; r < rows(); r++ ){
                if(r == xrow) continue;

                for(width_t c= 0; c < cols(); c++){
                    if( c == xcol ) continue;

                    result.set(get(r, c), currow, curcol);
                    curcol++;
                }

               currow++;
               curcol = 0;
            }
            cof = result.determinant();
        }

        return cof;
    }

    Matrix<elem_t> operator+(const elem_t& val) const{
        Matrix<elem_t> result(rows(), cols());

        for(width_t row = 0; row < result.rows(); row++){
            for(width_t col = 0; col < result.cols(); col++){
                result.set(get(row, col) + val, row, col);
            }
        }

        return result;
    }

    Matrix<elem_t> operator-(const elem_t& val) const{
        Matrix<elem_t> result(rows(), cols());

        for(width_t row = 0; row < result.rows(); row++){
            for(width_t col = 0; col < result.cols(); col++){
                result.set(get(row, col) - val, row, col);
            }
        }

        return result;
    }

    Matrix<elem_t> operator*(const elem_t& val) const{
        Matrix<elem_t> result(rows(), cols());

        for(width_t row = 0; row < result.rows(); row++){
            for(width_t col = 0; col < result.cols(); col++){
                result.set(get(row, col) * val, row, col);
            }
        }

        return result;
    }

    Matrix<elem_t> operator/(const elem_t& val) const{
        Matrix<elem_t> result(rows(), cols());

        for(width_t row = 0; row < result.rows(); row++){
            for(width_t col = 0; col < result.cols(); col++){
                result.set(get(row, col) / val, row, col);
            }
        }

        return result;
    }

    Matrix<elem_t> operator*(const Matrix<elem_t>& matrix) const {
        if(canMultiply(matrix)){
            Matrix<elem_t> result(rows(), matrix.cols());
            elem_t sum = 0;


            for(width_t row = 0; row < result.rows(); row++){
                for(width_t col = 0; col < result.cols(); col++){
                    for(int i = 0; i < cols(); i++){
                        sum += get(row, i) * matrix.get(i, col);
                    }

                    result.set(row, col, sum);
                    sum = 0;
                }
            }

            return result;
        }

        throw(0);
    }

    Matrix<elem_t> operator+(const Matrix<elem_t>& a) const {
        std::cout << "[Matrix] Add \n";
        if(a.canAdd(*this)){
            Matrix<elem_t> result(a.rows(), a.cols());

            elem_t sum = 0;
            width_t ccol = 0;

            for(width_t row = 0; row < result.rows(); row++){
                for(width_t col = 0; col < result.cols(); col++){
                    result.set(row, col, a.get(row, col) + this->get(row, col));
                }
            }

            //If we are adding a point to a point, ensure that it is not corrupt
            if(MatrixIsPoint(a) && MatrixIsPoint(*this))
            {
                if(result.get(3, 0) != 1){
                    result.set(1, 3, 0);
                }
            }

            //If we are adding a vect to a vect, ensure that it is not corrupt
            if(MatrixIsVector(a) && MatrixIsVector(*this))
            {
                if(result.get(3, 0) != 0){
                    result.set(0, 3, 0);
                }
            }

            return result;
        }

        throw(0);
    }

    Matrix<elem_t> operator-(const Matrix<elem_t>& a) const {
        if(canAdd(a)){
            Matrix<elem_t> result(rows(), cols());
            elem_t sum = 0;
            width_t ccol = 0;


            for(width_t row = 0; row < result.rows(); row++){
                for(width_t col = 0; col < result.cols(); col++){
                    result.set( get(row, col) - a.get(row, col), row, col);
                }
            }

            //If we are adding a point to a point, ensure that it is not corrupt
            if(MatrixIsPoint(a) && MatrixIsPoint(*this))
            {
                if(result.get(3, 0) != 1){
                    result.set(1, 3, 0);
                }
            }

            //If we are adding a vect to a vect, ensure that it is not corrupt
            if(MatrixIsVector(a) && MatrixIsVector(*this))
            {
                if(result.get(3, 0) != 0){
                    result.set(0, 0, 3);
                }
            }


            return result;
        }

        throw(0);
    }

    Matrix<elem_t> operator/(const Matrix& a){
        Matrix<elem_t> result = a;
        if(a.isSquare()){
            if(this->canMultiply(a)){
                result = *this * Inverse(a);
            }
        }

        return result;
    }

    inline bool outOfBounds(width_t row, width_t col) const{
        return (row+1 > rows() || col+1 > cols()) ? true : false;
    }

    inline elem_t get(width_t row, width_t col=0) const{
        elem_t result = 0;
        if(outOfBounds(row, col)){
            std::cout << "[Matrix][" << (int)row << ", " << (int)col << "] Index is out of bounds. Get failed.\n";
            throw(1);
        }else{
            result = m_matrix[row][col];
        }

        return result;
    }

    void set(elem_t val, width_t row, width_t col=0){
        if(!outOfBounds(row, col)){
            m_matrix[row][col] = val;
        }else{
            std::cout << "[Matrix][" << (int)row << ", " << (int)col << "] Index is out of bounds. Set Failed\n";
        }

    }

    inline bool canMultiply(const Matrix<elem_t>& matrix )const{
        if(cols() == matrix.rows()) return true;
        return false;
    }

    inline bool canAdd(const Matrix<elem_t>& matrix )const{
        std::cout << "[Matrix] canAdd \n";
        if(rows() == matrix.rows() && cols() == matrix.cols()){ std::cout << " true\n"; return true; }
        std::cout << " false\n";
        return false;
    }

    inline bool isSquare()const{
        return (rows() == cols());
    }

    inline width_t size()const{
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

    virtual inline void debug_output()const{

        for(width_t row = 0; row < rows(); row++){
            if(row == 0){
                std::cout << "{";
            }else{
                std::cout << " ";
            }
            std::cout << " ";

            for(width_t col = 0; col < cols(); col++){
                std::cout << get(row, col) << " ";
            }

            if(row == rows()-1){
                std::cout << "}\n" << std::endl;
            }

            std::cout << "\n";
        }
    }

};

#endif //MATRIX_H
