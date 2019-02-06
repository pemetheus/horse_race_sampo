#include "mainhorserace.h"
#include "ui_mainhorserace.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>
#include <iostream>
#include <algorithm>    // std::next_permutation, std::sort
#include <stdio.h>


#define MAX_NUMBER_OF_HORSES 15
#define MAX_NUMBERS_OF_ROWS 32760   


enum ExitCode
{
       Success,
       ParseFailure,
       ArgumentError,
       WriteError,
       FileFailure
};

typedef struct {
    int id;
    QString racetrack;
    int race_number;
    QString date;

}RACEINFO;

typedef struct {
    int id;
    int number;
    QString name;
    float odds;
    QString scratched;
    float jockey_trainer;
    float speed_E1;
    float speed_E2;
    float speed_late;
    float earnings;
    float wild_horse;


}HORSE;

typedef struct {
    int id;
    RACEINFO ri;
    HORSE    horse[MAX_NUMBER_OF_HORSES];
}RACECARD;



typedef struct
{
    int   type;
    int   horse_number;
    float m_l_odds;
        
}ROW;



typedef struct {
    
    int amount_of_rows;
        
            
    
}ANALYSIS;

RACECARD rc;

MainHorseRace::MainHorseRace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainHorseRace)
{
    const QString xmlFilePath;


    ui->setupUi(this);


}

MainHorseRace::~MainHorseRace()
{
    delete ui;
}


void MainHorseRace::on_load_race_card_btn_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Race Card"), "",
            tr("Race Card (*.xml);;All Files (*)"));



     if (fileName.isEmpty())
            return;
     else {


         QDomDocument doc;
         QFile file(fileName);
         if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
             return;

         QDomNodeList racetrack = doc.elementsByTagName("Place");
         QDomNode p = racetrack.item(0);

         QDomElement place = p.firstChildElement("Racetrack");
         QDomElement race = p.firstChildElement("RaceNumber");
         QDomElement date = p.firstChildElement("Date");

         rc.ri.racetrack = place.text().toAscii();
         rc.ri.race_number = race.text().toInt();
         rc.ri.date = date.text().toAscii();

         QDomNodeList horses = doc.elementsByTagName("Horse");

         std::cout << "Horses on the xml file :"  << horses.size() <<  std::endl;

         for (int i = 0; i < horses.size(); i++) {

             QDomNode n = horses.item(i);
             QDomElement number = n.firstChildElement("Number");
             QDomElement name = n.firstChildElement("Name");
             QDomElement odds = n.firstChildElement("Odds");
             QDomElement scratched = n.firstChildElement("Scratched");
             QDomElement joc_trainer = n.firstChildElement("Jockey_Trainer");
             QDomElement speed_E1 = n.firstChildElement("Speed_E1");
             QDomElement speed_E2 = n.firstChildElement("Speed_E2");
             QDomElement speed_late = n.firstChildElement("Speed_late");
             QDomElement earnings = n.firstChildElement("Earnings");
             QDomElement wild_horse = n.firstChildElement("WildHorse");


             std::cout << "Horse:" << number.text().toStdString() << " " << name.text().toStdString() << std::endl;

             rc.horse[i].number = number.text().toInt();
             rc.horse[i].name = name.text().toAscii();
             rc.horse[i].odds = odds.text().toFloat();
             rc.horse[i].scratched = scratched.text().toAscii();
             rc.horse[i].jockey_trainer = joc_trainer.text().toFloat();
             rc.horse[i].speed_E1 = speed_E1.text().toFloat();
             rc.horse[i].speed_E2 = speed_E2.text().toFloat();
             rc.horse[i].speed_late = speed_late.text().toFloat();
             rc.horse[i].earnings = earnings.text().toFloat();
             rc.horse[i].wild_horse = wild_horse.text().toFloat();


             if (number.isNull() || name.isNull() || odds.isNull())
                 continue;

//             std::cout << "Horse Number , name and Odds " << name. .toText() <<  std::endl;

//              Emma  Daddy MUMMY COMET
         }


     }

     UpdateData();

}


void MainHorseRace::on_clear_race_card_btn_clicked()
{
     std::cout << "Clearing Race Card " << std::endl;


     ResetData();



}

void MainHorseRace::on_quit_btn_clicked()
{
    std::cout << "Exiting Program" << std::endl;
    close();

}

void MainHorseRace::on_save_racecard_btn_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Race Card"), "",
            tr("Race Card (*.xml);;All Files (*)"));

    std::cout << "Save race file" << std::endl;

}

void MainHorseRace::UpdateData()
{

    this->ui->RaceTrack->setText(rc.ri.racetrack);
    this->ui->race_number->setValue(rc.ri.race_number);

    QDate Date = QDate::fromString(rc.ri.date,"MM/dd/yyyy");
    this->ui->race_day->setDate(Date);

    this->ui->horse1_name->setText(rc.horse[0].name);
    this->ui->horse1_odds->setValue(rc.horse[0].odds);
    this->ui->horse1_jockey_trainer_sldr->setValue(rc.horse[0].jockey_trainer);
    this->ui->horse1_speed_sldr->setValue(rc.horse[0].speed_E1);
    this->ui->horse1_speed_E2_sldr->setValue(rc.horse[0].speed_E2);
    this->ui->horse1_speed_late_sldr->setValue(rc.horse[0].speed_late);
    this->ui->horse1_earnings_sldr->setValue(rc.horse[0].earnings);
    this->ui->horse1_wild_sldr->setValue(rc.horse[0].wild_horse);

    this->ui->horse2_name->setText(rc.horse[1].name);
    this->ui->horse2_odds->setValue(rc.horse[1].odds);
    this->ui->horse2_jockey_trainer_sldr->setValue(rc.horse[1].jockey_trainer);
    this->ui->horse2_speed_sldr->setValue(rc.horse[1].speed_E1);
    this->ui->horse2_speed_E2_sldr->setValue(rc.horse[1].speed_E2);
    this->ui->horse2_speed_late_sldr->setValue(rc.horse[1].speed_late);
    this->ui->horse2_earnings_sldr->setValue(rc.horse[1].earnings);
    this->ui->horse2_wild_sldr->setValue(rc.horse[1].wild_horse);


    this->ui->horse3_name->setText(rc.horse[2].name);
    this->ui->horse3_odds->setValue(rc.horse[2].odds);
    this->ui->horse3_jockey_trainer_sldr->setValue(rc.horse[2].jockey_trainer);
    this->ui->horse3_speed_sldr->setValue(rc.horse[2].speed_E1);
    this->ui->horse3_speed_E2_sldr->setValue(rc.horse[2].speed_E2);
    this->ui->horse3_speed_late_sldr->setValue(rc.horse[2].speed_late);
    this->ui->horse3_earnings_sldr->setValue(rc.horse[2].earnings);
    this->ui->horse3_wild_sldr->setValue(rc.horse[2].wild_horse);


    this->ui->horse4_name->setText(rc.horse[3].name);
    this->ui->horse4_odds->setValue(rc.horse[3].odds);
    this->ui->horse4_jockey_trainer_sldr->setValue(rc.horse[3].jockey_trainer);
    this->ui->horse4_speed_sldr->setValue(rc.horse[3].speed_E1);
    this->ui->horse4_speed_E2_sldr->setValue(rc.horse[3].speed_E2);
    this->ui->horse4_speed_late_sldr->setValue(rc.horse[3].speed_late);
    this->ui->horse4_earnings_sldr->setValue(rc.horse[3].earnings);
    this->ui->horse4_wild_sldr->setValue(rc.horse[3].wild_horse);

    this->ui->horse5_name->setText(rc.horse[4].name);
    this->ui->horse5_odds->setValue(rc.horse[4].odds);
    this->ui->horse5_jockey_trainer_sldr->setValue(rc.horse[4].jockey_trainer);
    this->ui->horse5_speed_sldr->setValue(rc.horse[4].speed_E1);
    this->ui->horse5_speed_E2_sldr->setValue(rc.horse[4].speed_E2);
    this->ui->horse5_speed_late_sldr->setValue(rc.horse[4].speed_late);
    this->ui->horse5_earnings_sldr->setValue(rc.horse[4].earnings);
    this->ui->horse5_wild_sldr->setValue(rc.horse[4].wild_horse);

    this->ui->horse6_name->setText(rc.horse[5].name);
    this->ui->horse6_odds->setValue(rc.horse[5].odds);
    this->ui->horse6_jockey_trainer_sldr->setValue(rc.horse[5].jockey_trainer);
    this->ui->horse6_speed_sldr->setValue(rc.horse[5].speed_E1);
    this->ui->horse6_speed_E2_sldr->setValue(rc.horse[5].speed_E2);
    this->ui->horse6_speed_late_sldr->setValue(rc.horse[5].speed_late);
    this->ui->horse6_earnings_sldr->setValue(rc.horse[5].earnings);
    this->ui->horse6_wild_sldr->setValue(rc.horse[5].wild_horse);

    this->ui->horse7_name->setText(rc.horse[6].name);
    this->ui->horse7_odds->setValue(rc.horse[6].odds);
    this->ui->horse7_jockey_trainer_sldr->setValue(rc.horse[6].jockey_trainer);
    this->ui->horse7_speed_sldr->setValue(rc.horse[6].speed_E1);
    this->ui->horse7_speed_E2_sldr->setValue(rc.horse[6].speed_E2);
    this->ui->horse7_speed_late_sldr->setValue(rc.horse[6].speed_late);
    this->ui->horse7_earnings_sldr->setValue(rc.horse[6].earnings);
    this->ui->horse7_wild_sldr->setValue(rc.horse[6].wild_horse);

    this->ui->horse8_name->setText(rc.horse[7].name);
    this->ui->horse8_odds->setValue(rc.horse[7].odds);
    this->ui->horse8_jockey_trainer_sldr->setValue(rc.horse[7].jockey_trainer);
    this->ui->horse8_speed_sldr->setValue(rc.horse[7].speed_E1);
    this->ui->horse8_speed_E2_sldr->setValue(rc.horse[7].speed_E2);
    this->ui->horse8_speed_late_sldr->setValue(rc.horse[7].speed_late);
    this->ui->horse8_earnings_sldr->setValue(rc.horse[7].earnings);
    this->ui->horse8_wild_sldr->setValue(rc.horse[7].wild_horse);

    this->ui->horse9_name->setText(rc.horse[8].name);
    this->ui->horse9_odds->setValue(rc.horse[8].odds);
    this->ui->horse9_jockey_trainer_sldr->setValue(rc.horse[8].jockey_trainer);
    this->ui->horse9_speed_sldr->setValue(rc.horse[8].speed_E1);
    this->ui->horse9_speed_E2_sldr->setValue(rc.horse[8].speed_E2);
    this->ui->horse9_speed_late_sldr->setValue(rc.horse[8].speed_late);
    this->ui->horse9_earnings_sldr->setValue(rc.horse[8].earnings);
    this->ui->horse9_wild_sldr->setValue(rc.horse[8].wild_horse);

    this->ui->horse10_name->setText(rc.horse[9].name);
    this->ui->horse10_odds->setValue(rc.horse[9].odds);
    this->ui->horse10_jockey_trainer_sldr->setValue(rc.horse[9].jockey_trainer);
    this->ui->horse10_speed_sldr->setValue(rc.horse[9].speed_E1);
    this->ui->horse10_speed_E2_sldr->setValue(rc.horse[9].speed_E2);
    this->ui->horse10_speed_late_sldr->setValue(rc.horse[9].speed_late);
    this->ui->horse10_earnings_sldr->setValue(rc.horse[9].earnings);
    this->ui->horse10_wild_sldr->setValue(rc.horse[9].wild_horse);

    this->ui->horse11_name->setText(rc.horse[10].name);
    this->ui->horse11_odds->setValue(rc.horse[10].odds);
    this->ui->horse11_jockey_trainer_sldr->setValue(rc.horse[10].jockey_trainer);
    this->ui->horse11_speed_sldr->setValue(rc.horse[10].speed_E1);
    this->ui->horse11_speed_E2_sldr->setValue(rc.horse[10].speed_E2);
    this->ui->horse11_speed_late_sldr->setValue(rc.horse[10].speed_late);
    this->ui->horse11_earnings_sldr->setValue(rc.horse[10].earnings);
    this->ui->horse11_wild_sldr->setValue(rc.horse[10].wild_horse);

    this->ui->horse12_name->setText(rc.horse[11].name);
    this->ui->horse12_odds->setValue(rc.horse[11].odds);
    this->ui->horse12_jockey_trainer_sldr->setValue(rc.horse[11].jockey_trainer);
    this->ui->horse12_speed_sldr->setValue(rc.horse[11].speed_E1);
    this->ui->horse12_speed_E2_sldr->setValue(rc.horse[11].speed_E2);
    this->ui->horse12_speed_late_sldr->setValue(rc.horse[11].speed_late);
    this->ui->horse12_earnings_sldr->setValue(rc.horse[11].earnings);
    this->ui->horse12_wild_sldr->setValue(rc.horse[11].wild_horse);

    this->ui->horse13_name->setText(rc.horse[12].name);
    this->ui->horse13_odds->setValue(rc.horse[12].odds);
    this->ui->horse13_jockey_trainer_sldr->setValue(rc.horse[12].jockey_trainer);
    this->ui->horse13_speed_sldr->setValue(rc.horse[12].speed_E1);
    this->ui->horse13_speed_E2_sldr->setValue(rc.horse[12].speed_E2);
    this->ui->horse13_speed_late_sldr->setValue(rc.horse[12].speed_late);
    this->ui->horse13_earnings_sldr->setValue(rc.horse[12].earnings);
    this->ui->horse13_wild_sldr->setValue(rc.horse[12].wild_horse);

    this->ui->horse14_name->setText(rc.horse[13].name);
    this->ui->horse14_odds->setValue(rc.horse[13].odds);
    this->ui->horse14_jockey_trainer_sldr->setValue(rc.horse[13].jockey_trainer);
    this->ui->horse14_speed_sldr->setValue(rc.horse[13].speed_E1);
    this->ui->horse14_speed_E2_sldr->setValue(rc.horse[13].speed_E2);
    this->ui->horse14_speed_late_sldr->setValue(rc.horse[13].speed_late);
    this->ui->horse14_earnings_sldr->setValue(rc.horse[13].earnings);
    this->ui->horse14_wild_sldr->setValue(rc.horse[13].wild_horse);

    this->ui->horse15_name->setText(rc.horse[14].name);
    this->ui->horse15_odds->setValue(rc.horse[14].odds);
    this->ui->horse15_jockey_trainer_sldr->setValue(rc.horse[14].jockey_trainer);
    this->ui->horse15_speed_sldr->setValue(rc.horse[14].speed_E1);
    this->ui->horse15_speed_E2_sldr->setValue(rc.horse[14].speed_E2);
    this->ui->horse15_speed_late_sldr->setValue(rc.horse[14].speed_late);
    this->ui->horse15_earnings_sldr->setValue(rc.horse[14].earnings);
    this->ui->horse15_wild_sldr->setValue(rc.horse[14].wild_horse);
}

void MainHorseRace::ResetData()
{

    this->ui->RaceTrack->setText("<Enter the Place or Load Race Card>");
    this->ui->race_number->setValue(1);

    QDate Date = QDate::fromString("12/26/2018","MM/dd/yyyy");
    this->ui->race_day->setDate(Date);

    this->ui->horse1_name->setText("");
    this->ui->horse1_odds->setValue(0.0);
    this->ui->horse1_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse1_speed_sldr->setValue(0.0);
    this->ui->horse1_speed_E2_sldr->setValue(0.0);
    this->ui->horse1_speed_late_sldr->setValue(0.0);
    this->ui->horse1_earnings_sldr->setValue(0.0);
    this->ui->horse1_wild_sldr->setValue(0.0);

    this->ui->horse2_name->setText("");
    this->ui->horse2_odds->setValue(0.0);
    this->ui->horse2_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse2_speed_sldr->setValue(0.0);
    this->ui->horse2_speed_E2_sldr->setValue(0.0);
    this->ui->horse2_speed_late_sldr->setValue(0.0);
    this->ui->horse2_earnings_sldr->setValue(0.0);
    this->ui->horse2_wild_sldr->setValue(0.0);

    this->ui->horse3_name->setText("");
    this->ui->horse3_odds->setValue(0.0);
    this->ui->horse3_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse3_speed_sldr->setValue(0.0);
    this->ui->horse3_speed_E2_sldr->setValue(0.0);
    this->ui->horse3_speed_late_sldr->setValue(0.0);
    this->ui->horse3_earnings_sldr->setValue(0.0);
    this->ui->horse3_wild_sldr->setValue(0.0);

    this->ui->horse4_name->setText("");
    this->ui->horse4_odds->setValue(0.0);
    this->ui->horse4_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse4_speed_sldr->setValue(0.0);
    this->ui->horse4_speed_E2_sldr->setValue(0.0);
    this->ui->horse4_speed_late_sldr->setValue(0.0);
    this->ui->horse4_earnings_sldr->setValue(0.0);
    this->ui->horse4_wild_sldr->setValue(0.0);

    this->ui->horse5_name->setText("");
    this->ui->horse5_odds->setValue(0.0);
    this->ui->horse5_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse5_speed_sldr->setValue(0.0);
    this->ui->horse5_speed_E2_sldr->setValue(0.0);
    this->ui->horse5_speed_late_sldr->setValue(0.0);
    this->ui->horse5_earnings_sldr->setValue(0.0);
    this->ui->horse5_wild_sldr->setValue(0.0);

    this->ui->horse6_name->setText("");
    this->ui->horse6_odds->setValue(0.0);
    this->ui->horse6_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse6_speed_sldr->setValue(0.0);
    this->ui->horse6_speed_E2_sldr->setValue(0.0);
    this->ui->horse6_speed_late_sldr->setValue(0.0);
    this->ui->horse6_earnings_sldr->setValue(0.0);
    this->ui->horse6_wild_sldr->setValue(0.0);

    this->ui->horse7_name->setText("");
    this->ui->horse7_odds->setValue(0.0);
    this->ui->horse7_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse7_speed_sldr->setValue(0.0);
    this->ui->horse7_speed_E2_sldr->setValue(0.0);
    this->ui->horse7_speed_late_sldr->setValue(0.0);
    this->ui->horse7_earnings_sldr->setValue(0.0);
    this->ui->horse7_wild_sldr->setValue(0.0);

    this->ui->horse8_name->setText("");
    this->ui->horse8_odds->setValue(0.0);
    this->ui->horse8_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse8_speed_sldr->setValue(0.0);
    this->ui->horse8_speed_E2_sldr->setValue(0.0);
    this->ui->horse8_speed_late_sldr->setValue(0.0);
    this->ui->horse8_earnings_sldr->setValue(0.0);
    this->ui->horse8_wild_sldr->setValue(0.0);

    this->ui->horse9_name->setText("");
    this->ui->horse9_odds->setValue(0.0);
    this->ui->horse9_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse9_speed_sldr->setValue(0.0);
    this->ui->horse9_speed_E2_sldr->setValue(0.0);
    this->ui->horse9_speed_late_sldr->setValue(0.0);
    this->ui->horse9_earnings_sldr->setValue(0.0);
    this->ui->horse9_wild_sldr->setValue(0.0);

    this->ui->horse10_name->setText("");
    this->ui->horse10_odds->setValue(0.0);
    this->ui->horse10_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse10_speed_sldr->setValue(0.0);
    this->ui->horse10_speed_E2_sldr->setValue(0.0);
    this->ui->horse10_speed_late_sldr->setValue(0.0);
    this->ui->horse10_earnings_sldr->setValue(0.0);
    this->ui->horse10_wild_sldr->setValue(0.0);

    this->ui->horse11_name->setText("");
    this->ui->horse11_odds->setValue(0.0);
    this->ui->horse11_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse11_speed_sldr->setValue(0.0);
    this->ui->horse11_speed_E2_sldr->setValue(0.0);
    this->ui->horse11_speed_late_sldr->setValue(0.0);
    this->ui->horse11_earnings_sldr->setValue(0.0);
    this->ui->horse11_wild_sldr->setValue(0.0);

    this->ui->horse12_name->setText("");
    this->ui->horse12_odds->setValue(0.0);
    this->ui->horse12_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse12_speed_sldr->setValue(0.0);
    this->ui->horse12_speed_E2_sldr->setValue(0.0);
    this->ui->horse12_speed_late_sldr->setValue(0.0);
    this->ui->horse12_earnings_sldr->setValue(0.0);
    this->ui->horse12_wild_sldr->setValue(0.0);

    this->ui->horse13_name->setText("");
    this->ui->horse13_odds->setValue(0.0);
    this->ui->horse13_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse13_speed_sldr->setValue(0.0);
    this->ui->horse13_speed_E2_sldr->setValue(0.0);
    this->ui->horse13_speed_late_sldr->setValue(0.0);
    this->ui->horse13_earnings_sldr->setValue(0.0);
    this->ui->horse13_wild_sldr->setValue(0.0);

    this->ui->horse14_name->setText("");
    this->ui->horse14_odds->setValue(0.0);
    this->ui->horse14_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse14_speed_sldr->setValue(0.0);
    this->ui->horse14_speed_E2_sldr->setValue(0.0);
    this->ui->horse14_speed_late_sldr->setValue(0.0);
    this->ui->horse14_earnings_sldr->setValue(0.0);
    this->ui->horse14_wild_sldr->setValue(0.0);

    this->ui->horse15_name->setText("");
    this->ui->horse15_odds->setValue(0.0);
    this->ui->horse15_jockey_trainer_sldr->setValue(0.0);
    this->ui->horse15_speed_sldr->setValue(0.0);
    this->ui->horse15_speed_E2_sldr->setValue(0.0);
    this->ui->horse15_speed_late_sldr->setValue(0.0);
    this->ui->horse15_earnings_sldr->setValue(0.0);
    this->ui->horse15_wild_sldr->setValue(0.0);

}


void MainHorseRace::on_bet_size_valueChanged(const QString &arg1)
{
    this->ui->total->setValue(this->ui->bet_size->value()*this->ui->rows->value());
}

void MainHorseRace::on_rows_valueChanged(const QString &arg1)
{
    this->ui->total->setValue(this->ui->bet_size->value()*this->ui->rows->value());

}

void MainHorseRace::on_import_race_card_btn_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Race Card Import "), "",
            tr("Race Card HTML (*.html);;All Files (*)"));

    QString data;


    if (fileName.isEmpty())
            return;
    else {

         QFile file(fileName);

         if (!file.open(QIODevice::ReadOnly))
             return;

              int i=0;

              while(!file.atEnd())
              {

                  data = file.readLine();

                  if(data.contains("RACE_DATE=12/27/2018"))
                          std::cout << "Race info found" << std::endl;

                  i++;

              }
              std::cout << "i " << i << std::endl;




         file.close();

     }


}

void MainHorseRace::on_calculate_rows_clicked()
{


      int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
      int r = 4;
      int n = sizeof(arr)/sizeof(arr[0]);
      printCombination(arr, n, r);


}


// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void MainHorseRace::printCombination(int arr[], int n, int r)
{
    // A temporary array to store all combination one by one
    int data[r];

    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r);
}

/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void MainHorseRace::combinationUtil(int arr[], int data[], int start, int end,
                     int index, int r)
{
    static int rows = 0;

    // Current combination is ready to be printed, print it
    if (index == r)
    {
        for (int j=0; j<r; j++)
            printf("%d ", data[j]);
        printf("\n");
        return;
    }

    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r);
        rows++;
    }
    printf("Total %d rows\n",rows);

}


