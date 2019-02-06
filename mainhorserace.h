#ifndef MAINHORSERACE_H
#define MAINHORSERACE_H

#include <QMainWindow>

namespace Ui {
class MainHorseRace;
}

class MainHorseRace : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainHorseRace(QWidget *parent = 0);
    ~MainHorseRace();
    void UpdateData();
    void ResetData();
    void combinationUtil(int arr[], int data[], int start, int end,
                         int index, int r);
    void printCombination(int arr[], int n, int r);

private slots:
    void on_load_race_card_btn_clicked();
    void on_clear_race_card_btn_clicked();

    void on_quit_btn_clicked();

    void on_save_racecard_btn_clicked();

    void on_bet_size_valueChanged(const QString &arg1);

    void on_rows_valueChanged(const QString &arg1);

    void on_import_race_card_btn_clicked();

   void on_calculate_rows_clicked();

private:
    Ui::MainHorseRace *ui;


};

#endif // MAINHORSERACE_H
