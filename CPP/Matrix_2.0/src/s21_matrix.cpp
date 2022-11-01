#include "s21_matrix.h"

/*
 * CONSTRUCTORS && DESTRUCTOR
*/

S21Matrix::S21Matrix()
{
    _rows = 0;
    _columns = 0;
    _matrix = nullptr;
}

S21Matrix::S21Matrix(int rows, int columns)
{
    this->_rows = rows;
    this->_columns = columns;

    S21MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
{
    S21CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
{
    S21CopyMatrix(other);
    other.S21FreeMatrix();
}

S21Matrix::~S21Matrix()
{
    S21FreeMatrix();
}

/*
 * OPERATORS
*/

double& S21Matrix::operator()(int i, int j)
{
    assert(i < _rows && j < _columns);

    return _matrix[i][j];
}


S21Matrix S21Matrix::operator=(const S21Matrix &other)
{
    if (_matrix != nullptr)
    {
        S21FreeMatrix();
    }
    this->S21CopyMatrix(other);

    return *this;
}

bool S21Matrix::operator==(const S21Matrix &other)
{
    if (other._rows == _rows && other._columns == _columns)
    {
        if (this->S21EqMatrix(other)) return true;
    }

    return false;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21SumMatrix(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21SubMatrix(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator*(double other)
{
    S21Matrix MatrixTmp(*this);
    MatrixTmp.S21MulNumber(other);

    return MatrixTmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other)
{
    assert(_columns == other._rows);

    S21Matrix MatrixTmp(*this);
    return MatrixTmp.S21MulMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other)
{
    assert(other._rows == _rows && other._columns == _columns);

    S21SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*=(double other)
{
    S21MulNumber(other);

    return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other)
{
    assert(_columns == other._rows);
    S21Matrix MatrixTmp(*this);
    *this = MatrixTmp.S21MulMatrix(other);
    return *this;
}

/*
 * HELPERS
*/

bool S21Matrix::S21MemoryAllocation()
{
    if (_rows < 1 || _columns < 1)
    {
        return false;
    }

    _matrix = new double *[_rows];
    for (int i = 0; i < _rows; i++)
    {
        _matrix[i] = new double[_columns];
    }
    S21ZeroedMatrix();

    return true;
}

void S21Matrix::S21FreeMatrix()
{
    for (int i = 0; i < _rows; i++)
    {
        delete []_matrix[i];
    }
    delete []_matrix;

    _columns = 0;
    _rows = 0;
    _matrix = nullptr;
}

bool S21Matrix::S21EqMatrix(const S21Matrix &other) const
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            if (fabs(_matrix[i][j] - other._matrix[i][j]) > EPS)
            {
                return false;
            }
        }
    }

    return true;
}

void S21Matrix::S21CopyMatrix(const S21Matrix &other)
{
    this->_rows = other._rows;
    this->_columns = other._columns;
    S21MemoryAllocation();
    for (int i = 0; i < other._rows; i++)
    {
        for (int j = 0; j < other._columns; j++)
        {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

void S21Matrix::S21ZeroedMatrix()
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            this->_matrix[i][j] = 0.0;
        }
    }
}

void S21Matrix::S21SumMatrix(const S21Matrix &other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}

void S21Matrix::S21SubMatrix(const S21Matrix &other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}

void S21Matrix::S21MulNumber(double other)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] *= other;
        }
    }
}

S21Matrix S21Matrix::S21MulMatrix(const S21Matrix &other)
{
    S21Matrix ResultMatrix(_rows, other._columns);

    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < other._columns; j++)
        {
            for (int k = 0; k < other._rows; k++)
            {
                ResultMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return ResultMatrix;
}

void S21Matrix::S21OutputMatrix() const
{
    std::cout << "Output matrix(" << _rows << ", " << _columns << ")\n";
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
