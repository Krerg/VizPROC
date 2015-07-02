#ifndef PROGRAMMINFORMATIONWINDOW_H
#define PROGRAMMINFORMATIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

/**
 * @brief The ProgrammInformationWindow class Окно, показывающее информацию о программе
 */
class ProgrammInformationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ProgrammInformationWindow(QWidget *parent = 0);
    ~ProgrammInformationWindow();
private:
    /**
     * @brief information Лейбл с информацией о программе
     */
    QLabel* information;

    /**
     * @brief okButton кнопка закрытия окна
     */
    QPushButton* okButton;
signals:

public slots:
};

#endif // PROGRAMMINFORMATIONWINDOW_H
