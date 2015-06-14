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
     * @brief information
     */
    QLabel* information;

    /**
     * @brief okButton
     */
    QPushButton* okButton;
signals:

public slots:
};

#endif // PROGRAMMINFORMATIONWINDOW_H
