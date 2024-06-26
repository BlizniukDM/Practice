#include "dateTimeWidget.h"
#include <QDateTime>
#include <QLabel>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDialog>
#include <vector>
#include <string>
#include <cstring>
#include <QString>
#include <QTextEdit>
//#include <sstream>

using namespace std;

DateTimeWidget::DateTimeWidget(QWidget *parent) : QWidget(parent)
{
    dateTimeLineEdit = new QLineEdit(this);
    calendarButton = new QPushButton("...", this);
    textEdit = new QTextEdit(this);
    dateTimeLineEdit->setFixedSize(300,30);
    // Set size and position for textEdit
    textEdit->setFixedSize(300, 300);  // Example size
    textEdit->move(5000, 100);  // Example position
    validationLabel = new QLabel(this);
    validationLabel->setFixedSize(200,30);
    validationLabel->move(100,100);
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(dateTimeLineEdit);
    inputLayout->addWidget(calendarButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(textEdit);  // Add textEdit to the layout

    setLayout(mainLayout);
    calendarButton->setFixedSize(70,30);
    calendarButton->setStyleSheet("background-color: grey");
    selectedDate = QDate::currentDate();
    selectedTime = QTime::currentTime();

    connect(calendarButton, &QPushButton::clicked, this, &DateTimeWidget::showCalendar);
    //connect(dateTimeLineEdit, &QLineEdit::editingFinished, this, &DateTimeWidget::validateAndUpdateDateTime);
    connect(dateTimeLineEdit, &QLineEdit::textEdited, this, &DateTimeWidget::on_dateTimeLineEdit_textEdited);
}

void DateTimeWidget::showCalendar()
{
    QDialog *calendarDialog = new QDialog(this, Qt::Popup);
    calendarDialog->setFixedSize(300, 300);

    QVBoxLayout *dialogLayout = new QVBoxLayout(calendarDialog);
    QCalendarWidget *calendarWidget = new QCalendarWidget(calendarDialog);
    dialogLayout->addWidget(calendarWidget);
    calendarDialog->setLayout(dialogLayout);

    QPoint buttonPos = calendarButton->mapToGlobal(QPoint(0, 0));
    calendarDialog->move(buttonPos.x() + calendarButton->width(), buttonPos.y());

    connect(calendarWidget, &QCalendarWidget::clicked, [this, calendarDialog, calendarWidget](const QDate &date) {
        selectedDate = date;
        updateDateTimeLineEdit();
        calendarDialog->accept();
    });

    calendarDialog->exec();
}

void DateTimeWidget::updateDateTimeLineEdit()
{
    QString dateTimeString = selectedDate.toString("dd:MM:yyyy") + " " + selectedTime.toString("HH:mm:ss");
    dateTimeLineEdit->setText(dateTimeString);
    on_dateTimeLineEdit_textEdited(dateTimeLineEdit->text());

}

void DateTimeWidget::validateAndUpdateDateTime()
{
    QString dateTimeString = dateTimeLineEdit->text();
    QRegularExpression re("^(\\d{2}):(\\d{2}):(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})$");
    QRegularExpressionMatch match = re.match(dateTimeString);

    if (match.hasMatch())
    {
        int day = match.captured(1).toInt();
        int month = match.captured(2).toInt();
        int year = match.captured(3).toInt();
        int hour = match.captured(4).toInt();
        int minute = match.captured(5).toInt();
        int second = match.captured(6).toInt();

        if (QDate::isValid(year, month, day) && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
        {
            selectedDate.setDate(year, month, day);
            selectedTime.setHMS(hour, minute, second);
        }
        else
        {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid date and time.");
            updateDateTimeLineEdit();
        }
    }
    else
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter the date and time in the format DD:MM:YYYY HH:MM:SS.");
        updateDateTimeLineEdit();
    }
}

map<string, string> ordinalMap = {
    {"ноль", "нулевого"},
    {"один", "первого"},
    {"два", "второго"},
    {"три", "третьего"},
    {"четыре", "четвёртого"},
    {"пять", "пятого"},
    {"шесть", "шестого"},
    {"семь", "седьмого"},
    {"восемь", "восьмого"},
    {"девять", "девятого"},
    {"десять", "десятого"},
    {"одиннадцать", "одиннадцатого"},
    {"двенадцать", "двенадцатого"},
    {"тринадцать", "тринадцатого"},
    {"четырнадцать", "четырнадцатого"},
    {"пятнадцать", "пятнадцатого"},
    {"шестнадцать", "шестнадцатого"},
    {"семнадцать", "семнадцатого"},
    {"восемнадцать", "восемнадцатого"},
    {"девятнадцать", "девятнадцатого"},
    {"двадцать", "двадцатого"},
    {"тридцать", "тридцатого"},
    {"сорок", "сорокового"},
    {"пятьдесят", "пятидесятого"},
    {"шестьдесят", "шестидесятого"},
    {"семьдесят", "семидесятого"},
    {"восемьдесят", "восьмидесятого"},
    {"девяносто", "девяностого"},
    {"сто", "сотого"},
    {"двести", "двухсотого"},
    {"триста", "трёхсотого"},
    {"четыреста", "четырёхсотого"},
    {"пятьсот", "пятисотого"},
    {"шестьсот", "шестисотого"},
    {"семьсот", "семисотого"},
    {"восемьсот", "восьмисотого"},
    {"девятьсот", "девятисотого"},
    {"тысяча", "тысячного"},
    {"две тысячи", "двухтысячного"},
    {"три тысячи", "трёхтысячного"},
    {"четыре тысячи", "четырёхтысячного"},
    {"пять тысяч", "пятитысячного"},
    {"шесть тысяч", "шеститысячного"},
    {"семь тысяч", "семитысячного"},
    {"восемь тысяч", "восьмитысячного"},
    {"девять тысяч", "девятитысячного"}
};

map<string, string> ordinalMap1 = {
    {"ноль", "нулевая"},
    {"один", "первая"},
    {"два", "вторая"},
    {"три", "третяя"},
    {"четыре", "четвёртая"},
    {"пять", "пятая"},
    {"шесть", "шестая"},
    {"семь", "седьмая"},
    {"восемь", "восьмая"},
    {"девять", "девятая"},
    {"десять", "десятая"},
    {"одиннадцать", "одиннадцатая"},
    {"двенадцать", "двенадцатая"},
    {"тринадцать", "тринадцатая"},
    {"четырнадцать", "четырнадцатая"},
    {"пятнадцать", "пятнадцатая"},
    {"шестнадцать", "шестнадцатая"},
    {"семнадцать", "семнадцатая"},
    {"восемнадцать", "восемнадцатая"},
    {"девятнадцать", "девятнадцатая"},
    {"двадцать", "двадцатая"},
    {"тридцать", "тридцатая"},
    {"сорок", "сороковая"},
    {"пятьдесят", "пятидесятая"},
    {"шестьдесят", "шестидесятая"},
    {"семьдесят", "семидесятая"},
    {"восемьдесят", "восьмидесятая"},
    {"девяносто", "девяностая"},
    {"сто", "сотая"},
    {"двести", "двухсотая"},
    {"триста", "трёхсотая"},
    {"четыреста", "четырёхсотая"},
    {"пятьсот", "пятисотая"},
    {"шестьсот", "шестисотая"},
    {"семьсот", "семисотая"},
    {"восемьсот", "восьмисотая"},
    {"девятьсот", "девятисотая"},
    {"тысяча", "тысячная"},
    {"две тысячи", "двухтысячная"},
    {"три тысячи", "трёхтысячная"},
    {"четыре тысячи", "четырёхтысячная"},
    {"пять тысяч", "пятитысячная"},
    {"шесть тысяч", "шеститысячная"},
    {"семь тысяч", "семитысячная"},
    {"восемь тысяч", "восьмитысячная"},
    {"девять тысяч", "девятитысячная"}
};

map<int,string> months = {
    {0, ""},
    {1, "января"},
    {2, "февраля"},
    {3, "марта"},
    {4, "апреля"},
    {5, "мая"},
    {6, "июня"},
    {7, "июля"},
    {8, "августа"},
    {9, "сентября"},
    {10, "октября"},
    {11, "ноября"},
    {12, "декабря"}
};

vector<string> numRev = {""};
std::vector<std::string> belowTwenty = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять", "десять",
                                        "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать",
                                        "семнадцать", "восемнадцать", "девятнадцать"};
std::vector<std::string> belowTwentymin = {"", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять", "десять",
                                           "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать",
                                           "семнадцать", "восемнадцать", "девятнадцать"};
std::vector<std::string> tens = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
std::vector<std::string> hundreds = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
std::vector<std::string> thousands = {"", "тысяча", "две тысячи", "три тысячи", "четыре тысячи", "пять тысяч", "шесть тысяч", "семь тысяч", "восемь тысяч", "девять тысяч"};
vector<string> times = {"минут", "минуты", "часов", "часа", "секунд", "секунды"};
vector<string> times2 = {"минутa", "минуты", "часов", "часа", "секундa", "секунды"};
std::string numberToWordsYear(int num) {
    std::string result;
    int temp;
    if (num >= 1000) {
        temp = num;
        if(temp % 1000 == 0) {
            int thousandsPart = num / 1000;
            result += ordinalMap.at(thousands[thousandsPart]) + " года";
            num %= 1000;
        } else {
            int thousandsPart = num / 1000;
            result += thousands[thousandsPart] + " ";
            num %= 1000;
        }

    }

    if (num >= 100) {
        temp = num;
        if(temp % 100 == 0) {
            int hundredsPart = num / 100;
            result += ordinalMap.at(hundreds[hundredsPart]) + " года";
            num %= 100;
        } else {
            int hundredsPart = num / 100;
            result += hundreds[hundredsPart] + " ";
            num %= 100;
        }
    }

    if (num >= 20) {
        temp = num;
        if(temp % 10 == 0) {
            int tensPart = num / 10;
            result += ordinalMap.at(tens[tensPart]) + " года";
            num %= 10;
        } else {
            int tensPart = num / 10;
            result += tens[tensPart] + " ";
            num %= 10;
        }
    }

    if (num > 0) {
        result += ordinalMap.at(belowTwenty[num]) + " года";
    }

    return result;
}

std::string numberToWordsDays(int num) {
    std::string result;
    int temp;
    if (num >= 1000) {
        temp = num;
        if(temp % 1000 == 0) {
            int thousandsPart = num / 1000;
            result += ordinalMap.at(thousands[thousandsPart]) + " ";
            num %= 1000;
        } else {
            int thousandsPart = num / 1000;
            result += thousands[thousandsPart] + " ";
            num %= 1000;
        }

    }

    if (num >= 100) {
        temp = num;
        if(temp % 100 == 0) {
            int hundredsPart = num / 100;
            result += ordinalMap.at(hundreds[hundredsPart]) + " ";
            num %= 100;
        } else {
            int hundredsPart = num / 100;
            result += hundreds[hundredsPart] + " ";
            num %= 100;
        }
    }

    if (num >= 20) {
        temp = num;
        if(temp % 10 == 0) {
            int tensPart = num / 10;
            result += ordinalMap.at(tens[tensPart]) + " ";
            num %= 10;
        } else {
            int tensPart = num / 10;
            result += tens[tensPart] + " ";
            num %= 10;
        }
    }

    if (num > 0) {
        result += ordinalMap.at(belowTwenty[num]) + " ";
    }

    return result;
}

std::string numberToWordsTime(int num, int temp) {
    std::string result;

    if (num >= 100) {
        if(num%100 == 0) {
            int hundredsPart = num / 100;
            result += hundreds[hundredsPart] + " " + times[temp];
            num %= 100;
        } else {
            int hundredsPart = num / 100;
            result += hundreds[hundredsPart] + " ";
            num %= 100;
        }
    }

    if (num >= 20) {
        if(num%10 == 0) {
            int tensPart = num / 10;
            result += tens[tensPart] + " " + times[temp];
            num %= 10;
        } else {
            int tensPart = num / 10;
            result += tens[tensPart] + " ";
            num %= 10;
        }
    }

    if (num > 0) {
        if(num > 0 && num < 5) {
            if((temp == 0 || temp == 4) && num == 1) {
                result += belowTwentymin[num] + " " + times2[temp];
            } else {
                result += belowTwentymin[num] + " " + times[temp + 1];
            }

        } else {
            result += belowTwenty[num] + " " + times[temp];
        }
    }

    return result;
}

void DateTimeWidget::on_dateTimeLineEdit_textEdited(const QString &arg1)
{
    vector<string> tokens;
    string line_copy;
    string item;
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
    string line = arg1.toStdString();
    char* line_new = new char [line.length()+1];
    strcpy(line_new, line.c_str());
    char* token = strtok(line_new, " .:,;*?\t");
    while (token != nullptr) {
        string str(token);
        tokens.push_back(str);
        token = strtok(NULL, " .:,;*?\t");
    }
    int temp = 0;
    delete[] line_new;
    string sresult = "";
    if(tokens.size() == 1 || tokens.size() > 1) {

        //validationLabel->setText(QString::number(day));
        temp = stoi(tokens[0]);
        day = temp;
        sresult += numberToWordsDays(temp) + " ";
    }

    if(tokens.size() == 2 || tokens.size() > 2) {

        //validationLabel->setText(QString::number(temp));
        temp = stoi(tokens[1]);
        month = temp;
        sresult += months.at(temp) + " ";
    }

    if(tokens.size() == 3 || tokens.size() > 3) {

        //validationLabel->setText(QString::number(temp));
        temp = stoi(tokens[2]);
        year = temp;
        sresult += numberToWordsYear(temp) + "\n";
    }

    if(tokens.size() == 4 || tokens.size() > 4) {

        //validationLabel->setText(QString::number(temp));
        temp = stoi(tokens[3]);
        hour = temp;
        sresult += numberToWordsTime(temp, 2) + " ";
    }

    if(tokens.size() == 5 || tokens.size() > 5) {

        //validationLabel->setText(QString::number(temp));
        temp = stoi(tokens[4]);
        minute = temp;
        sresult += numberToWordsTime(temp, 0) + " ";
    }

    if(tokens.size() == 6) {

        //validationLabel->setText(QString::number(temp));
        temp = stoi(tokens[5]);
        second = temp;
        sresult += numberToWordsTime(temp, 4);
    }

    textEdit->setText(QString::fromStdString(sresult));

    /*QString dateTimeString = dateTimeLineEdit->text();
    QRegularExpression re("^(\\d{2}):(\\d{2}):(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})$");
    QRegularExpressionMatch match = re.match(dateTimeString);*/



    if (QDate::isValid(year, month, day) && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
    {
        selectedDate.setDate(year, month, day);
        selectedTime.setHMS(hour, minute, second);
        validationLabel->setText("");
    }
    else
    {
        //QMessageBox::warning(this, "Invalid Input", "Please enter a valid date and time.");
        //validationLabel->setText("Неправильно записана дата");
        textEdit->setText(QString::fromStdString("Неправильно записана дата"));
        //updateDateTimeLineEdit();
    }

    /*//QMessageBox::warning(this, "Invalid Input", "Please enter the date and time in the format DD:MM:YYYY HH:MM:SS.");
        //updateDateTimeLineEdit();
        //validationLabel->setText("Неправильно записана дата");
        textEdit->setText(QString::fromStdString("Неправильно записана дата"));*/

}
