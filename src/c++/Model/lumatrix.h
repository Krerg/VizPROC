#ifndef LUMATRIX_H
#define LUMATRIX_H

#include <QObject>

/**
 * @brief The LUMatrix class класс для решения матрицы методом LU разложения
 */
class LUMatrix : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief LUMatrix конструктор класса
     * @param parent указатель на предка
     */
    explicit LUMatrix(QObject *parent = 0);

    /**
     * @brief setA установка матрицы A
     * @param a
     */
    void setA(double** a);

    /**
     * @brief setB установка матрицы B
     * @param b
     */
    void setB(double* b);

    /**
     * @brief compute вычисление ответа
     * @param n кол-во неизвестных
     * @return массив неизвестных размерностью n
     */
    double* compute(int n);

    /**
     * @brief printMatrix вывод матрицы размерности n*n
     * @param matrix
     * @param n
     */
    void printMatrix(double** matrix, int n);
private:
    /**
     * @brief a
     */
    double** a;

    /**
     * @brief b
     */
    double* b;

    /**
     * @brief l
     */
    double** l;

    /**
     * @brief u
     */
    double** u;

    /**
     * @brief x
     */
    double* x;

    /**
     * @brief y
     */
    double* y;
signals:

public slots:

};

#endif // LUMATRIX_H
