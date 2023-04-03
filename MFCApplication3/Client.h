#pragma once
#include <afxdb.h>
#include <vector>
#include "afxdb.h"
#include <thread> 
//#include <future>
#include <atomic>
#include <memory>
#include <string>

namespace condition
{
	class Status
	{
	public:
		//Status();
		//~Status();
		enum class CurrentStatus : int8_t
			//ReadingBD - состояние, когда программа просто считывает данные, вмешательство не требуется {вызывается перед чтением бд}
			//Wait* - переключить программу в режим ожидания события {вызывается сразу после события, как триггер}
			//MessageDelay - после выведенного [сообщения] подождать несколько секунд, чтобы кассир успел прочитать его, затем перейти к WaitForCustomer
		{
			//!можно в методах, использующих READINGDB добавить параметр предыдущего состояния, чтобы после ридинг он возращался к предыдущему состоянию (любому)
			WAIT4CUSTOMER = 1, READINGDB, WAIT4CASSIER_AD, WAIT4CASSIER_DC, MESSAGEDELAY, STRESSQUIT
		};
		void ChangeCurrentStatus(CurrentStatus status);
		CurrentStatus GetCurrentStatus();
	protected:
		//std::atomic<CurrentStatus> shareData{ CurrentStatus::WAIT4CUSTOMER };
		CurrentStatus shareData{ CurrentStatus::WAIT4CUSTOMER };
	};
}

//низкоуровневое открытие\создание файла, запись настроек
namespace file 
{
	class Settings
	{
	public:
		/// \brief проверка на наличие файла настроек
		bool CheckSettingsFile(std::string& m_refDB, std::string& m_refServer);
		std::string& GetDB();
		std::string& GetServer();

		//std::string& m_refDB= m_pDB;
		//std::string& m_refServer= m_pServer;
	private:
		std::string m_pDB;
		std::string m_pServer;
	};
	//
	class Log
	{
	public:
		static bool WriteLog(CString ErrorString);
		static CString GetTimeNow(char EventTime);
	};
}

namespace userspace 
{
	//у кассира и у покупателя есть поля, которые должны быть у обоих (имя, фамилия, кейкод), значит User - их родительский класс
	class User
	{
	public:
		//User() = default;
		//~User();
		/// \brief получение в одной строке ФИО
		CString GetUserData();
		/// \brief вставка в поля объекта данных
		bool SetInfo(CString KeyCode, CString FirstName, CString MiddleName, CString LastName);//, CByteArray Photo);
		/// \brief получение кейкода
		CString GetKeyCode();
		/// \brief установка в поле кейкода
		void SetKeyCode(CString KeyCode);
	protected:
		CString m_pKeyCode;//ID пропуска
		CString m_pFirstName;
		CString m_pMiddleName;
		CString m_pLastName;
	};

	class Customer : public User
	{

	public:

		bool SetStatus_UsedDiscountToday();
		
		void SetPhoto(CLongBinary& Photo);
		CLongBinary GetPhoto();
		//CByteArray& GetPhoto();
		CString GetMutableKeyCode(DWORD caseLunchCode);
		CString GetMutableKeyCode(CString caseLunchCode);
		CString GetInfoAbout();
		CString GetTabNumber();
		bool GetUserExist();
		void SetUserExist(bool UserExist);

		short unsigned int Set_CountOfFailures();
		void SetStatus_UsedDiscountToday(bool status);
		void Set_CountOfFailures(short unsigned int Count);
		void SetTabNumber(CString TabNumber);

	private:
		bool m_bpUserExist = false;

		//CByteArray m_pPhotob;  //
		CLongBinary pPhotolb;
		//Скидка использовалась сегодня - проверяется первым, если == true, значит перенаправить на 
		//возможность отмены предоставленной скидки
		//если false - вывести - предоставление скидки доступно
		bool m_bpUsedDiscountToday = false;

		//число повторных попыток получения скидки за 1 и тот же день (без учета уже предоставленной)
		short unsigned int m_pCountOfFailures = 0;
		CString m_pMutableKC;
		CString m_pTabNumber;//ID табельного

	};

	class Cassier : public User
	{
	public:
		CString GetInfoAbout();
		bool SetInfoAbout(CString TabNumber, CString FirstName, CString MiddleName, CString LastName);
	private:
		short int m_countOfAcceptedDiscountsToday = 0;
		short int m_countOfNullifiedDiscountsToday = 0;
	};
}

class Client 
{
public:
	const int YESCODE = ******;
	const int NOCODE = ******;
	Client() = default;

	void LoadPhotoFromDBintoVar(BLOB Photo);
	void SavePhotoIntoFile(CDBVariant Photo);

	/// \brief получение пользовательских данных из бд
	/// \note метод загружает данные во внутреннюю структуру данных, используя метод класса SetInfo()         
	void GetUserData(CString MutableKeyCode);
	/// \brief отправка SQL-запроса в бд с проверкой - открытое ли соединение
	void ExecuteSQL(CString SQL);
	/// \brief подключение к бд
	/// \note метод проверяет, есть ли на диске файл с настроками, если да - пытается подключиться по этим данным 
	/// если нет, грузит настройки по умолчанию
	bool ConnectToDB();
	/// \brief закрытие подключения
	bool DisconnectFromDB();
	/// \brief запись в файл переданной строки
	//bool WriteLog(CString ErrorString);
	/// \brief проверка наличия пользователя с определенным кейкодом в бд
	bool ThisUserExist(CString KeyCodeMutant);
	/// \brief проверка использования в текущий день скидки
	bool CheckDiscountThisUserToday(CString TabNumber);
	/// \brief получение последнего кода в бд
	long GetLatestCode();
	/// \brief получение даты и времени в определенном форматировании в зависимости от полученного символа
	//CString GetTimeNow(char EventTime);
	/// \brief преобразование CString в long и получение табельного номера 
	CString GetTabNumber(CString MutableKeyCode);
	/// \brief получение табельного номера 
	CString GetTabNumber(long nKey);
	/// \brief опрос бд на наличие нового кода не-от-кассира
	/// \note 1 - начать процедуру обработки кода | 0 - не начинать
	bool WatchChangesInDB();
	/// \brief отмена предоставления скидки и устранение циклического вывода ПД после делея
	/// \note (после того, как время на решение у кассира истекло)
	/// \note если cof == 1,  то к числу ошибок для данного пользователя добавляется 1 
	void Aborting(CString why, bool COF);
	/// \brief получение последнего пользовательского кода из базы
	DWORD GetLatestUserCode();

	void ReConnect();

	//userspace::Cassier& GetCassier();
	//userspace::Customer& GetCustomer();
	//condition::Status& GetStatus();
	//file::Settings& GetSettings();
	userspace::Cassier m_Cassier;
	userspace::Customer m_Customer;
	condition::Status m_Status;
	file::Settings m_Settings;
	


	//std::vector <std::string> m_Settings;
	CDatabase m_cdb;

	
};

//каркас
/*
class Watcher
{

private:
	std::jthread m_thr;
	Client m_MSSQLServer;
	std::atomic_bool m_runnin;

public:
	Watcher() : m_thr(&Watcher::Thread, this) //автоматический запуск при создании объекта - не нужен
		//лучше сначала проинициализировать все нужные данные, потом запускать поток (.Thread())
	{
		
	}
	~Watcher();//while (!exit_flag) {}
	bool ShowValueStopToken();
	void SetValueStopToken(std::stop_token stop_token);
	void Thread();
	void Watch_Status4ChangeLogic();
}; */