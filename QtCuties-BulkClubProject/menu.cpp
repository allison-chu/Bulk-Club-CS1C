#include "menu.h"
#include "ui_menu.h"
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QFileInfo>
#include "mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    if(mydb.open())
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }



        mydb = QSqlDatabase::addDatabase("QSQLITE");
        dataPath = QFileDialog::getExistingDirectory(this, tr("Open Data Folder"),
                                                 "/Users/SeanVHatfield/SeanHatfield/Documents/GitHub/Bulk-Club-CS1C/QtCuties-BulkClubProject",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);


        mydb.setDatabaseName(dataPath + "/database.db");


        if (!mydb.open())
        {
            qDebug() << ("Failed to open the database");

        }
        else
        {
            qDebug() << ("Database Connected");

        }

        loadFirstSalesReport();

        QSqlQuery query;
//        bool firstLine=true;
//        query.prepare("SELECT * FROM customerTable");
//        if(query.exec())
//        {
//            while (query.next())
//            {
//                const QSqlRecord recrd = query.record();
//                if(firstLine)
//                {
//                    for(int i = 0;i < recrd.count();++i)
//                    {
//                        qDebug() << recrd.field(i); //Headers
//                    }
//                }
//                firstLine=false;
//                for(int i = 0;i < recrd.count();++i)
//                {
//                    outTest << recrd.value(i).toString();
//                    outTest << endl;

//                }
//            }
//        }

        query.prepare("SELECT FROM customerTable WHERE Name *");
        query.exec();
        QString itemName;
//        ui->comboBoxDeleteName->addItem()

}

Menu::~Menu()
{
    delete ui;
}




void Menu::on_load_all_clicked()
{


    //Customer Name
    //Member #
    //Customer Type
    //Membership Expiration Date

    QString tempName;
    QString tempMemberNumber;
    QString tempCustomerType;
    QString tempMembershipExp;

    QFile file(dataPath + "/warehouse shoppers.txt");
//      QFile file(dataPath + "/testingDatabase.txt");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);




    QSqlQueryModel * modal = new QSqlQueryModel();

    QSqlQuery* qry = new QSqlQuery(this->mydb);

    qry->prepare("delete from customerTable");
    qry->exec();

    for (int i = 0; !in.atEnd(); i++)
    {
        tempName = in.readLine();
        tempMemberNumber = in.readLine();
        tempCustomerType = in.readLine();
        tempMembershipExp = in.readLine();

        qDebug() << "Name: " << tempName;
        qDebug() << "Membership Number: " << tempMemberNumber;
        qDebug() << "Customer Type: " << tempCustomerType;
        qDebug() << "Membership Expiration Date: " << tempMembershipExp;

        qry->prepare("insert into customerTable (Name,Number,Type,Expiration)" "VALUES ('"+tempName+"', '"+tempMemberNumber+"', '"+tempCustomerType+"', '"+tempMembershipExp+"')");
        qry->exec();

    }

    qry->prepare("select * from customerTable");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableViewDisplayMember->setModel(modal);
    ui->tableViewDisplayMember->resizeColumnsToContents();

    qDebug() << (modal->rowCount());

}


void Menu::on_comboBoxDays_activated(const QString &arg1)
{
    QString argVar;
    argVar = arg1;
    daySelected = arg1;

    qDebug() << "ArgVar: " << argVar;

    QString textName;

    int tempIndex = 0;
    tempIndex = ui->comboBoxDays->currentIndex() + 1;
    textName = "day" + textName + QString::number(tempIndex) + ".txt";

    qDebug() << "Text name: " << textName;



    //    Date of purchase
    //    Customer number who bought the product
    //    Product description
    //    Price of product
    //    Quantity

        QString tempDate;
        QString tempCustomerNum;
        QString tempDescription;
        QString tempPrice;
        QString tempQuantity;

        QFile file(dataPath + "/" + textName);

        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "title", "file not open");
        }
        QTextStream in(&file);




        QSqlQueryModel * modal = new QSqlQueryModel();

        QSqlQuery* qry = new QSqlQuery(this->mydb);

        qry->prepare("delete from '"+argVar+"'");
        qry->exec();

        for (int i = 0; !in.atEnd(); i++)
        {
            tempDate = in.readLine();
            tempCustomerNum = in.readLine();
            tempDescription = in.readLine();
            tempPrice = in.readLine();
            tempQuantity = in.readLine();

            qDebug() << "Date: " << tempDate;
            qDebug() << "Customer Number: " << tempCustomerNum;
            qDebug() << "Description: " << tempDescription;
            qDebug() << "Price: " << tempPrice;
            qDebug() << "Quantity: " << tempQuantity;

            qry->prepare("insert into '"+argVar+"' (Date,Number,Description,Price,Quantity)" "VALUES ('"+tempDate+"', '"+tempCustomerNum+"', '"+tempDescription+"', '"+tempPrice+"', '"+tempQuantity+"')");
            if(qry->exec())
            {
                qDebug() << "Success!";

            }
            else {
                qDebug() << qry->lastError().text();
            }

        }

        qry->prepare("select * from '"+argVar+"'");

        qry->exec();
        modal->setQuery(*qry);
        ui->salesReportTableView->setModel(modal);
        ui->salesReportTableView->resizeColumnsToContents();

        qDebug() << (modal->rowCount());

}

void Menu::loadFirstSalesReport()
{
    //Load Sunday on salesReportTableView when window is opened


    //    Date of purchase
    //    Customer number who bought the product
    //    Product description
    //    Price of product
    //    Quantity

        QString tempDate;
        QString tempCustomerNum;
        QString tempDescription;
        QString tempPrice;
        QString tempQuantity;

        QFile file(dataPath + "/day1.txt");

        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "title", "file not open");
        }
        QTextStream in(&file);


        QSqlQueryModel * modal = new QSqlQueryModel();

        QSqlQuery* qry = new QSqlQuery(this->mydb);

        qry->prepare("delete from Sunday");
        qry->exec();
        for (int i = 0; !in.atEnd(); i++)
        {

            tempDate = in.readLine();
            tempCustomerNum = in.readLine();
            tempDescription = in.readLine();
            tempPrice = in.readLine();
            tempQuantity = in.readLine();

            qDebug() << "Date: " << tempDate;
            qDebug() << "Customer Number: " << tempCustomerNum;
            qDebug() << "Description: " << tempDescription;
            qDebug() << "Price: " << tempPrice;
            qDebug() << "Quantity: " << tempQuantity;

            qry->prepare("insert into Sunday (Date,Number,Description,Price,Quantity)" "VALUES ('"+tempDate+"', '"+tempCustomerNum+"', '"+tempDescription+"', '"+tempPrice+"', '"+tempQuantity+"')");
            if(qry->exec())
            {
                qDebug() << "Success!";

            }
            else {
                qDebug() << qry->lastError().text();
            }
        }

        qry->prepare("select * from Sunday");

        qry->exec();
        modal->setQuery(*qry);
        ui->salesReportTableView->setModel(modal);
        ui->salesReportTableView->resizeColumnsToContents();

        qry->prepare("select SUM(Price) from Sunday");

        if(qry->exec())
        {
            qDebug() << "Success!";

        }
        else {
            qDebug() << qry->lastError().text();
        }

        QString totalRevenue = qry->value("Price").toString();

        qDebug() << totalRevenue;

        qDebug() << (modal->rowCount());


        //END Load Sunday
}

void Menu::on_checkBoxStandard_toggled(bool checked)
{
//    QSqlQueryModel * modal = new QSqlQueryModel();
//    QSqlQuery* qry = new QSqlQuery(this->mydb);

//    qry->prepare("");
//    qry->exec();

//    modal->setQuery(*qry);
//    ui->salesReportTableView->setModel(modal);
//    ui->salesReportTableView->resizeColumnsToContents();

    qDebug() << checked;
}

void Menu::on_standardButton_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(this->mydb);

    qry->prepare("select * from '"+daySelected+"' where customerTable.Number = '"+daySelected+"'.Number and Type = Regular");

    if(qry->exec())
    {
        qDebug() << "Success!";

    }
    else {
        qDebug() << qry->lastError().text();
    }

    modal->setQuery(*qry);
    ui->salesReportTableView->setModel(modal);
    ui->salesReportTableView->resizeColumnsToContents();
}

void Menu::on_buttonAddCustomer_clicked()
{
    QFile file(dataPath + "/warehouse shoppers.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        qDebug() << "File not open\n";
    }
    QString date = "12/31/2021";
    QTextStream outCustomer(&file);

    outCustomer << endl;
    outCustomer << ui->lineEditAddName->text() << endl;
    outCustomer << ui->lineEditAddMemberNum->text() << endl;
    QString addMemberStatus;
    if(ui->addCustomerStatus->currentIndex() == 0)
    {
        addMemberStatus = "Executive";
    }
    else if(ui->addCustomerStatus->currentIndex() == 1)
    {
        addMemberStatus = "Standard";
    }

    outCustomer << addMemberStatus << endl;
    outCustomer << date;

    ui->lineEditAddName->setText("");
    ui->lineEditAddMemberNum->setText("");

    QMessageBox::information(this, tr("Customer Info"), tr("Customer Added!"));
}



void Menu::on_saveDatabaseTxt_clicked()
{
    QFile file(dataPath + "/warehouse shoppers.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        qDebug() << "File not open\n";
    }

    QTextStream outTest(&file);
    QSqlQuery query;
    bool firstLine=true;
    query.prepare("SELECT * FROM customerTable");
    if(query.exec())
    {
        while (query.next())
        {
            const QSqlRecord recrd = query.record();
            if(firstLine)
            {
                for(int i = 0;i < recrd.count();++i)
                {
                    qDebug() << recrd.field(i); //Headers
                }
            }
            firstLine=false;
            for(int i = 0;i < recrd.count();++i)
            {
                outTest << recrd.value(i).toString();
                outTest << endl;

            }
        }
    }
}
