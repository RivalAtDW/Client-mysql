// ConsoleTestWorker.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Client.h"
#include <random>
int main()
{
    setlocale(LC_ALL, "rus");
    Client client;
    std::cout << "Hello World!\n";
    std::cout << "Enter the 1 - insert into random valid KeyCode!\n";
    std::cout << "Enter the 2 - insert into unvalid KeyCode!\n";
    std::cout << "Enter the 3 - insert into YESCODE!\n";
    std::cout << "Enter the 4 - insert into NOCODE!\n";
    std::cout << "Enter the 5 - drop DB [Discounts]!\n";
    //std::cout << "Enter the 6 - show DB [Discounts]!\n";
    std::cout << "Enter the 0 - exit!\n";
    int8_t in=0;
  
        while (in != '0')
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> o(1, 12);
            enum code { 
                c11111 = 1,         
                c22222, 
                c33333,
                c44444,
                c55555,
                c66666,
                c77777, 
                c88888,
                c99999,
                c100000,
                c200000,
                c300000
            } s;

            std::cin >> in;
            
            switch (in)
            {
              



            case '1':
            {

                //auto id = (o)(gen);
                s = static_cast<code> ((o)(gen));
                CString who;
                std::cout <<"# "<< s << " был выбран случайно. \t";
                switch (s)
                {
                case c11111:
                    who = _T("11111");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString()<<"\n";
                    break;
                case c22222:
                    who = _T("22222");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c33333:
                    who = _T("33333");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c44444:
                    who = _T("44444");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c55555:
                    who = _T("55555");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c66666:
                    who = _T("66666");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c77777:
                    who = _T("77777");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c88888:
                    who = _T("88888");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c99999:
                    who = _T("99999");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c100000:
                    who = _T("100000");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c200000:
                    who = _T("200000");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                case c300000:
                    who = _T("300000");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                default:
                    who = _T("13920");
                    std::cout << "Кейкод - ";
                    std::wcout << who.GetString() << "\n";
                    break;
                }
                try {
                    client.ConnectToDB();
                    if (client.m_cdb.IsOpen()) {
                        client.ExecuteSQL(_T("INSERT INTO [DBName].[ShemeName].[TableName] (Fld_1, Fld_2) VALUES(" + who + ", GETDATE());"));
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;
            case '2':
            {
                try 
                {
                    client.ConnectToDB();
                    if (client.m_cdb.IsOpen()) {
                        client.ExecuteSQL(_T("INSERT INTO[DBName].[ShemeName].[TableName] (Fld_1, Fld_2) VALUES(1234567890, GETDATE());"));
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;
            case '3':
            {
                try
                {
                    client.ConnectToDB();
                    if (client.m_cdb.IsOpen()) {
                        client.ExecuteSQL(_T("INSERT INTO[DBName].[ShemeName].[TableName] (Fld_1, Fld_2) VALUES(******, GETDATE());"));
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                    catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;
            case '4':
            {
                try
                {
                    client.ConnectToDB(); 
                    if (client.m_cdb.IsOpen()) {
                        client.ExecuteSQL(_T("INSERT INTO[DBName].[ShemeName].[TableName] (Fld_1, Fld_2) VALUES(******, GETDATE());"));
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                    catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;
            case '5':
            {
                try
                {
                    client.ConnectToDB();
                    if (client.m_cdb.IsOpen()) {
                        client.ExecuteSQL(_T("delete FROM[DBName].[ShemeName].[TableName]"));
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;

            case '6':
            {
                try
                {
                
                        client.ConnectToDB();
                        if (client.m_cdb.IsOpen()) {
                        //vector res=client.ShowResultDB();
                        client.DisconnectFromDB();
                        std::cout << "SQL-запрос отправлен \n";
                    }
                    else {
                        std::cout << "Нет подключения \n";
                    }
                }
                catch (CDBException& e)
                {
                    std::wcout << e.m_strError << "\n";
                }
            }
            break;
            default:
                break;
            }



        }
    
  

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
