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
			//ReadingBD - ���������, ����� ��������� ������ ��������� ������, ������������� �� ��������� {���������� ����� ������� ��}
			//Wait* - ����������� ��������� � ����� �������� ������� {���������� ����� ����� �������, ��� �������}
			//MessageDelay - ����� ����������� [���������] ��������� ��������� ������, ����� ������ ����� ��������� ���, ����� ������� � WaitForCustomer
		{
			//!����� � �������, ������������ READINGDB �������� �������� ����������� ���������, ����� ����� ������ �� ���������� � ����������� ��������� (������)
			WAIT4CUSTOMER = 1, READINGDB, WAIT4CASSIER_AD, WAIT4CASSIER_DC, MESSAGEDELAY, STRESSQUIT
		};
		void ChangeCurrentStatus(CurrentStatus status);
		CurrentStatus GetCurrentStatus();
	protected:
		//std::atomic<CurrentStatus> shareData{ CurrentStatus::WAIT4CUSTOMER };
		CurrentStatus shareData{ CurrentStatus::WAIT4CUSTOMER };
	};
}

//�������������� ��������\�������� �����, ������ ��������
namespace file 
{
	class Settings
	{
	public:
		/// \brief �������� �� ������� ����� ��������
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
	//� ������� � � ���������� ���� ����, ������� ������ ���� � ����� (���, �������, ������), ������ User - �� ������������ �����
	class User
	{
	public:
		//User() = default;
		//~User();
		/// \brief ��������� � ����� ������ ���
		CString GetUserData();
		/// \brief ������� � ���� ������� ������
		bool SetInfo(CString KeyCode, CString FirstName, CString MiddleName, CString LastName);//, CByteArray Photo);
		/// \brief ��������� �������
		CString GetKeyCode();
		/// \brief ��������� � ���� �������
		void SetKeyCode(CString KeyCode);
	protected:
		CString m_pKeyCode;//ID ��������
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
		//������ �������������� ������� - ����������� ������, ���� == true, ������ ������������� �� 
		//����������� ������ ��������������� ������
		//���� false - ������� - �������������� ������ ��������
		bool m_bpUsedDiscountToday = false;

		//����� ��������� ������� ��������� ������ �� 1 � ��� �� ���� (��� ����� ��� ���������������)
		short unsigned int m_pCountOfFailures = 0;
		CString m_pMutableKC;
		CString m_pTabNumber;//ID ����������

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

	/// \brief ��������� ���������������� ������ �� ��
	/// \note ����� ��������� ������ �� ���������� ��������� ������, ��������� ����� ������ SetInfo()         
	void GetUserData(CString MutableKeyCode);
	/// \brief �������� SQL-������� � �� � ��������� - �������� �� ����������
	void ExecuteSQL(CString SQL);
	/// \brief ����������� � ��
	/// \note ����� ���������, ���� �� �� ����� ���� � ����������, ���� �� - �������� ������������ �� ���� ������ 
	/// ���� ���, ������ ��������� �� ���������
	bool ConnectToDB();
	/// \brief �������� �����������
	bool DisconnectFromDB();
	/// \brief ������ � ���� ���������� ������
	//bool WriteLog(CString ErrorString);
	/// \brief �������� ������� ������������ � ������������ �������� � ��
	bool ThisUserExist(CString KeyCodeMutant);
	/// \brief �������� ������������� � ������� ���� ������
	bool CheckDiscountThisUserToday(CString TabNumber);
	/// \brief ��������� ���������� ���� � ��
	long GetLatestCode();
	/// \brief ��������� ���� � ������� � ������������ �������������� � ����������� �� ����������� �������
	//CString GetTimeNow(char EventTime);
	/// \brief �������������� CString � long � ��������� ���������� ������ 
	CString GetTabNumber(CString MutableKeyCode);
	/// \brief ��������� ���������� ������ 
	CString GetTabNumber(long nKey);
	/// \brief ����� �� �� ������� ������ ���� ��-��-�������
	/// \note 1 - ������ ��������� ��������� ���� | 0 - �� ��������
	bool WatchChangesInDB();
	/// \brief ������ �������������� ������ � ���������� ������������ ������ �� ����� �����
	/// \note (����� ����, ��� ����� �� ������� � ������� �������)
	/// \note ���� cof == 1,  �� � ����� ������ ��� ������� ������������ ����������� 1 
	void Aborting(CString why, bool COF);
	/// \brief ��������� ���������� ����������������� ���� �� ����
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

//������
/*
class Watcher
{

private:
	std::jthread m_thr;
	Client m_MSSQLServer;
	std::atomic_bool m_runnin;

public:
	Watcher() : m_thr(&Watcher::Thread, this) //�������������� ������ ��� �������� ������� - �� �����
		//����� ������� ������������������� ��� ������ ������, ����� ��������� ����� (.Thread())
	{
		
	}
	~Watcher();//while (!exit_flag) {}
	bool ShowValueStopToken();
	void SetValueStopToken(std::stop_token stop_token);
	void Thread();
	void Watch_Status4ChangeLogic();
}; */