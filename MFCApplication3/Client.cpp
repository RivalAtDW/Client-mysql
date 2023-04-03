#include "pch.h"
#include "Client.h"
#include < fstream >
#include <string>
#include <future>
#include "MFCApplication3.h"

//Returns a LONG - A 32 - bit signed integer.
#define MAKELONG(a, b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
//Returns a WORD - A 16 - bit unsigned integer.
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
//Returns a WORD - A 16 - bit unsigned integer.
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))

//using namespace condition;
//using namespace file;
//using namespace userspace;

//userspace::User::~User()
//{
//}


CString userspace::Customer::GetMutableKeyCode(DWORD LunchCode)
{
	CString Sword1;
	CString Sword2;
	Sword1 = std::to_string(LOWORD(LunchCode)).c_str();
	Sword2 = std::to_string(HIWORD(LunchCode)).c_str();
	m_pMutableKC=(Sword2 + '/' + Sword1);
	return m_pMutableKC;
}

CString userspace::Customer::GetMutableKeyCode(CString caseLunchCode)
{
	unsigned int LunchCode = (unsigned int)_ttoi(caseLunchCode);
	DWORD key = static_cast<DWORD>(LunchCode);
	return GetMutableKeyCode(key);
}

CString userspace::Customer::GetTabNumber()
{
	return m_pTabNumber;
}

bool userspace::Customer::GetUserExist()
{
	return m_bpUserExist;
}

void userspace::Customer::SetUserExist(bool UserExist)
{
	m_bpUserExist = UserExist;
}

bool userspace::Customer::SetStatus_UsedDiscountToday()
{
	return m_bpUsedDiscountToday;
}

void userspace::Customer::SetPhoto(CLongBinary& Photo)
{
	CBitmap place;
//	place.LoadOEMBitmap(Photo);
	
}


void userspace::Customer::SetStatus_UsedDiscountToday(bool status)
{
	m_bpUsedDiscountToday= status;
}


short unsigned int userspace::Customer::Set_CountOfFailures()
{
	return m_pCountOfFailures;
}

void userspace::Customer::Set_CountOfFailures(short unsigned int Count)
{
	m_pCountOfFailures = Count;
}

void userspace::Customer::SetTabNumber(CString TabNumber)
{
	m_pTabNumber = TabNumber;
}

bool userspace::User::SetInfo(CString KeyCode, CString FirstName, CString MiddleName, CString LastName)//, CByteArray Photo)
{
	m_pKeyCode = KeyCode;
	m_pFirstName = FirstName;
	m_pMiddleName = MiddleName;
	m_pLastName = LastName;
	//p_Photo.Copy(Photo);
	return false;
}

CString userspace::User::GetKeyCode()
{
	return m_pKeyCode;
}

void userspace::User::SetKeyCode(CString KeyCode)
{
	m_pKeyCode = KeyCode;
}




void Client::ExecuteSQL(CString SQL)
{
	if (m_cdb.IsOpen()) 
	{
		m_cdb.ExecuteSQL(SQL);
	}
}


bool  Client::ConnectToDB()
{	
	std::string& m_refDB = m_Settings.GetDB();
	std::string& m_refServer = m_Settings.GetServer();
	//try to check existing settings file, if not - create him and write defaults values
	if (m_Settings.CheckSettingsFile(m_refDB, m_refServer))
	{
		try
		{
			CString server(m_refServer.c_str());
			CString db(m_refDB.c_str());

			CString con = _T("Driver={SQL Server};Server=" )+ server + _T(";Database=")+ db + _T(";Option=3;TrustedConnection=Yes;") ;
			file::Log::WriteLog(_T("App open, Connecting..."));
			m_cdb.OpenEx(con, CDatabase::noOdbcDialog);
			if (m_cdb.CanUpdate()) {
				file::Log::WriteLog(_T("Update Yes"));
			}
			if (m_cdb.CanTransact())
				file::Log::WriteLog(_T("Transact Yes"));
		}
		//catch (...)
		catch (CDBException* e)
		{
			file::Log::WriteLog(_T("\tОшибка подключения к базе данных. Обратитесь к системному администратору"));
			file::Log::WriteLog(e->m_strError);
			m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::STRESSQUIT);
			m_refServer = "ServerName\\InstanceName";
			m_refDB = "DBName";
		
			e->Delete();
		}


	}
	else {
		try
		{
			file::Log::WriteLog(_T("App open, Connecting..."));
			m_cdb.OpenEx(_T("Driver={SQL Server};Server=ServerName\\InstanceName;Database=DBName;Option=3;TrustedConnection=Yes;", CDatabase::noOdbcDialog));
			if (m_cdb.CanUpdate()) {
				file::Log::WriteLog(_T("Update Yes"));
			}
			if (m_cdb.CanTransact())
				file::Log::WriteLog(_T("Transact Yes"));
		}
		//catch (...)
			catch (CDBException* e)
		{
			file::Log::WriteLog(_T("\tОшибка подключения к базе данных. Обратитесь к системному администратору"));
			file::Log::WriteLog(e->m_strError);
			m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::STRESSQUIT);
			e->Delete();
		}
	}
	return false;
}

bool Client::DisconnectFromDB()
{
	if (m_cdb.IsOpen())
	{
		try { m_cdb.Close(); }
		catch (CDBException* e) {
			file::Log::WriteLog(e->m_strError); e->Delete();
		}
	}

	if (m_cdb.IsOpen())
	{
		file::Log::WriteLog(_T("db alive after closing!"));
		return true;
	}
	else file::Log::WriteLog(_T("db closed correct"));
	return false;
}

//1 file exist | 0 does not
bool file::Settings::CheckSettingsFile(std::string& m_refDB, std::string& m_refServer)
{
	std::ifstream fileIsExist("settings.ini");
	std::vector <std::string> m_Settings;
	if (fileIsExist)
	{//файл существует, значит можно его поюзать
		std::string temp;
		for (fileIsExist >> temp; !fileIsExist.eof(); fileIsExist >> temp)
		{
			m_Settings.push_back(temp);
		}
			//if size ==4, тогда возможно, что синтаксис файла верен
		if (m_Settings.size() == 4)
		{
			for (size_t i = 0; i < m_Settings.size(); i++)
			{
				//можно упростить и ничего не удалять, а обращаться к элементам [1], [3]
				if (m_Settings.at(i) == "Server:" || m_Settings.at(i) == "Database:")
				{
					m_Settings.erase(m_Settings.begin() + i);//эмуляция удаления по индексу
					std::vector<std::string>(m_Settings).swap(m_Settings);
				}
			}

			m_refServer = m_Settings[0].data();
			m_refDB = m_Settings[1].data();

			return true;
		}
	}else 

	{
		try
		{
			std::ofstream Newfile("settings.ini", std::ios::binary | std::ios::app);
			Newfile << "Server: ServerName\\InstanceName" <<  "\n";
			Newfile << "Database: DBName" << "\n";
			Newfile.close();
			m_refServer = "ServerName\\InstanceName";
			m_refDB = "DBName";
			return false;
		}
		catch (std::ofstream::failure e)
		{
			file::Log::WriteLog(_T("\tОшибка открытия файла логов. Обратитесь к системному администратору"));
		}

	}
	return false;
}

std::string& file::Settings::GetDB()
{
	return m_pDB;
}

std::string& file::Settings::GetServer()
{
	return m_pServer;
}

bool file::Log::WriteLog(CString ErrorString)
{
	std::ifstream fileIsExist("client.log");
	if (fileIsExist.bad())
	{
		try
		{
			std::ofstream fileOut("client.log");
			fileOut << CT2A(ErrorString) << " // localtime: " << CT2A(GetTimeNow(' ')) << "\n";
			fileOut.close();
		}
		catch (std::ofstream::failure e)
		{
			file::Log::WriteLog(_T("\tОшибка создания файла логов. Обратитесь к системному администратору"));
		}
	}
	else
	{
		try
		{
			std::ofstream fileOut("client.log", std::ios::binary | std::ios::app); 
			fileOut << CT2A(ErrorString) << " // localtime: " << CT2A(GetTimeNow(' ')) << "\n";
			fileOut.close();
		}
		catch (std::ofstream::failure e)
		{
			file::Log::WriteLog(_T("\tОшибка открытия файла логов. Обратитесь к системному администратору"));
		}

	}
	return false;
}

CString file::Log::GetTimeNow(char EventTime)
{
	struct tm newtime;
	__time32_t aclock;
	auto const bufSize = 32;

	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	CString year;
	year.Format(_T("%d"), newtime.tm_year + 1900);
	CString month;
	month.Format(_T("%d"), newtime.tm_mon + 1);
	if ((unsigned int)_ttoi(month) < 10)
	{
		month = _T("0") + month;
	}
	CString day;
	switch (newtime.tm_wday)
	{
	case 0:
		day = _T("Воскресенье");
		break;

	case 1:
		day = _T("Понедельник");
		break;

	case 2:
		day = _T("Вторник");
		break;

	case 3:
		day = _T("Среда");
		break;

	case 4:
		day = _T("Четверг");
		break;

	case 5:
		day = _T("Пятница");
		break;

	case 6:
		day = _T("Суббота");
		break;
	default:
		break;
	}
	CString DayN;
	DayN.Format(_T("%d"), newtime.tm_mday);
	if ((unsigned int)_ttoi(DayN) < 10)
	{
		DayN = _T("0") + DayN;
	}
	CString Hour;
	Hour.Format(_T("%d"), newtime.tm_hour);
	if ((unsigned int)_ttoi(Hour) < 10)
	{
		Hour = _T("0") + Hour;
	}
	CString min;
	min.Format(_T("%d"), newtime.tm_min);
	if ((unsigned int)_ttoi(min) < 10)
	{
		min = _T("0") + min;
	}
	CString sec;
	sec.Format(_T("%d"), newtime.tm_sec);
	if ((unsigned int)_ttoi(sec) < 10)
	{
		sec = _T("0") + sec;
	}



	switch (EventTime)
	{
	case '.':
		//sql-like 2022-12-07 10:30:10.000
		return CString(year + _T("-") + month + _T("-") + DayN + _T(" ") + Hour + _T(":") + min + _T(":") + sec + _T(".000"));
		break;
	case ',':
		//sql-like just date
		return CString(year + _T("-") + month + _T("-") + DayN);
		break;
	default:
		//logfile 11:03:22 Среда 07/12/2022
		return CString(Hour + _T(":") + min + _T(":") + sec + _T(" ") + day + _T(" ") + DayN + _T("/") + month + _T("/") + year);
		break;
	}
}


bool Client::CheckDiscountThisUserToday(CString TabNumber)
{
	if (m_cdb.IsOpen()) {
		CRecordset cr(&m_cdb);
		CString SqlDate = file::Log::GetTimeNow(',');
		CString Sword1 = _T("SELECT * FROM [TableName] where [Fld_1] LIKE '%") + TabNumber + _T("%' and [Fld_2] > '") + SqlDate + _T("'");
		cr.Open(CRecordset::forwardOnly, Sword1, CRecordset::readOnly);
		if (cr.GetRecordCount() == 0)
		{
			cr.Close();
			m_Customer.SetStatus_UsedDiscountToday(false);
			return m_Customer.SetStatus_UsedDiscountToday();
		}
		else
		{
			cr.Close();
			file::Log::WriteLog(_T("Ошибка - Пользователь уже пользовался скидкой сегодня"));
			m_Customer.SetStatus_UsedDiscountToday(true);
			return m_Customer.SetStatus_UsedDiscountToday();
		}
	}
	m_Customer.SetStatus_UsedDiscountToday(false);
	return m_Customer.SetStatus_UsedDiscountToday();

}


long Client::GetLatestCode()
{
	CString LunchCode;
	if (m_cdb.IsOpen())
	{
		CRecordset cr(&m_cdb);
		try
		{
			cr.Open(CRecordset::forwardOnly, _T("SELECT TOP (1) [Fld_1], [Fld_2] FROM [TableName]  order by [Fld_1] desc "), CRecordset::readOnly);
			if (cr.GetRecordCount() != 0) {
				cr.GetFieldValue(_T("Fld_2"), LunchCode);
				cr.Close();

			}
		}
		catch (CDBException& e)
		{
			file::Log::WriteLog(e.m_strError);
			e.Delete();
			file::Log::WriteLog(_T("Ошибка выборки данных, обратитесь к системному администратору"));
		}
	}
	
	return static_cast<long>((long)_ttoi(LunchCode));
}

DWORD Client::GetLatestUserCode()
{
	CString LunchCode;
	if (m_cdb.IsOpen())
	{
		CRecordset cr(&m_cdb);
		try
		{
			cr.Open(CRecordset::forwardOnly, _T("SELECT TOP (1) [Fld_1], [Fld_2] FROM [TableName] where [Fld_2] <> ****** and  [Fld_2] <> ****** order by [Fld_1] desc "), CRecordset::readOnly);
			if (cr.GetRecordCount() != 0) {
				cr.GetFieldValue(_T("Fld_2"), LunchCode);



				cr.Close();
			}
		}
		catch (CDBException& e)
		{
			file::Log::WriteLog(e.m_strError);
			e.Delete();
			file::Log::WriteLog(_T("Ошибка выборки данных, обратитесь к системному администратору"));
		}
	}
	return static_cast<DWORD>((unsigned int)_ttoi(LunchCode));
}

void Client::ReConnect()
{
}
/*
userspace::Cassier& Client::GetCassier()
{
	return m_Cassier;
}

userspace::Customer& Client::GetCustomer()
{
	return m_Customer;
}

condition::Status& Client::GetStatus()
{
	return m_Status;
}

file::Settings& Client::GetSettings()
{
	return m_Settings;
}
*/
CString userspace::User::GetUserData()
{
	return m_pFirstName + _T(" ") + m_pMiddleName + _T(" ") + m_pLastName;
}



bool Client::ThisUserExist(CString KeyCodeMutant)
{
	CRecordset cr(&m_cdb);
	if (m_cdb.IsOpen()) {
		CString SqlDate = file::Log::GetTimeNow(',');
		CString Sword1;
		CString TabNumber;
		Sword1 = _T("SELECT TOP 1 [Fld_1],[Fld_2],[Fld_3] FROM [TableName] where [FLd_2] LIKE '%") + KeyCodeMutant + _T("%';");
		cr.Open(CRecordset::forwardOnly, Sword1, CRecordset::readOnly);
		if (cr.GetRecordCount() != 0) {
			cr.GetFieldValue(_T("Fld_3"), TabNumber);


			//load to fields
			
			//cr.Close();
			//Sword1.Empty();
			//SqlDate.Empty();
			//KeyCodeMutant.Empty();
			//TabNumber.Empty();
			m_Customer.SetUserExist(true);

			
			return m_Customer.GetUserExist();
		}
		else { file::Log::WriteLog(_T("Ошибка - Пользователя с таким пропуском: ") + KeyCodeMutant + _T(" не существует")); }
	}
	m_Customer.SetUserExist(false);
	return m_Customer.GetUserExist();
}

CString Client::GetTabNumber(CString MutableKeyCode)
{
	CString TabNumber;
	unsigned int LunchCode = (unsigned int)_ttoi(MutableKeyCode);
	DWORD key = static_cast<DWORD>(LunchCode);
	return GetTabNumber(key);
}
CString Client::GetTabNumber(long nKey)
{
	CString TabNumber;
	if (m_cdb.IsOpen())
	{
		CRecordset cr(&m_cdb);
		try
		{
			
			auto key = nKey;
			CString Sword1;
			CString Sword2;
			CString KeyCodeMutant;
			Sword1 = std::to_string(LOWORD(key)).c_str();
			Sword2 = std::to_string(HIWORD(key)).c_str();
			KeyCodeMutant = Sword2 + '/' + Sword1;
			Sword1 = _T("SELECT TOP 1 [Fld_1],[Fld_2],[Fld_3] FROM [TableName] where [Fld_2] LIKE '%") + KeyCodeMutant + _T("%';");
			cr.Open(CRecordset::forwardOnly, Sword1, CRecordset::readOnly);
			if (cr.GetRecordCount() != 0)
			{
				cr.GetFieldValue(_T("Fld_2"), TabNumber);
			}
			cr.Close();
		}
		catch (CDBException& e)
		{
			file::Log::WriteLog(e.m_strError);
			e.Delete();
			file::Log::WriteLog(_T("Ошибка выборки данных, обратитесь к системному администратору"));
		}
	}
	return TabNumber;
}

bool Client::WatchChangesInDB()
{
	try
	{
		long latestCode = GetLatestCode();
		if (latestCode != YESCODE && latestCode != NOCODE )//&& thisUserExist)
		{
			m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::READINGDB);
			CString KC;
			KC.Format(_T("%d"), latestCode);
			m_Customer.SetKeyCode(KC);
			m_Customer.SetTabNumber(GetTabNumber(latestCode));
			return true;
		}
	}

	catch (CDBException& e)
	{
		file::Log::WriteLog(e.m_strError);
		e.Delete();
	}
	return false;
	
	//return CString();
}
void Client::Aborting(CString why, bool COF)
{
	//bool COF=1 => update count of failures++ in db, else - nope 
	CString SqlDate = file::Log::GetTimeNow('.');
	file::Log::WriteLog(why);
	if (COF) 
	{
		CString sqlAdd = _T("UPDATE [TableName] SET [Fld_1]=[Fld_1]+1 WHERE [Fld_2]='") + m_Customer.GetTabNumber() + _T("' AND [Fld_3] >'") + SqlDate + _T("'");
		file::Log::WriteLog(_T("EXECUTING... :") + sqlAdd);
		ExecuteSQL(sqlAdd);
			}


	try
	{
		CString sqlAdd = _T("INSERT INTO [TableName] (Fld_1, Fld_2) VALUES (******, '") + SqlDate + _T("')");
		file::Log::WriteLog(_T("EXECUTING... :") + sqlAdd);
		ExecuteSQL(sqlAdd);
	}
	catch (CDBException& e)
	{
		file::Log::WriteLog(e.m_strError);
		e.Delete();
	}

	m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::MESSAGEDELAY);

}

CString userspace::Cassier::GetInfoAbout()
{
	return CString();
}



void Client::LoadPhotoFromDBintoVar(BLOB Photo)
{
	BLOB blob;



}

void Client::SavePhotoIntoFile(CDBVariant Photo)
{
	BYTE* dataptr = (BYTE*)GlobalLock(Photo.m_pbinary->m_hData);
	CString pszFileName =_T("client.jpg");//"c:\\userdata\\tabnumber.jpg";
	CFile myfile;
	myfile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite);
	myfile.Write(Photo.m_pbinary->m_hData, Photo.m_pbinary->m_dwDataLength);
	myfile.Close();
	GlobalUnlock(Photo.m_pbinary->m_hData);
	ShellExecute(NULL, _T("open"), pszFileName, NULL, NULL, SW_SHOW);
}

void Client::GetUserData(CString MutableKeyCode)
{
		CString res;
		
		if (m_cdb.IsOpen()) {
			CRecordset cr(&m_cdb);
			CString SqlDate = file::Log::GetTimeNow('.');
			CString Sword1 = _T("SELECT TOP 1 [Fld_1],[Fld_2],[Fld_3],[Fld_4],[Fld_5],[Fld_6],[Fld_7] FROM [TableName] where [Fld_3] LIKE '%") + MutableKeyCode + _T("%';");
			cr.Open(CRecordset::forwardOnly, Sword1, CRecordset::readOnly);
			if (cr.GetRecordCount() != 0) {
				CString TabNumber;
				CString FirstName;
				CString MiddleName;
				CString LastName;
				CDBVariant Photo;
				cr.GetFieldValue(_T("TabNumber"), TabNumber);
				cr.GetFieldValue(_T("FirstName"), FirstName);
				cr.GetFieldValue(_T("MiddleName"), MiddleName);
				cr.GetFieldValue(_T("LastName"), LastName);
				cr.GetFieldValue(_T("Photo"), Photo);
				m_Customer.SetInfo(TabNumber, FirstName, MiddleName, LastName);
				res = FirstName + _T(" ") + MiddleName + _T(" ") + LastName;
				CImage image;
				BYTE* dataptr = (BYTE*)GlobalLock(Photo.m_pbinary->m_hData);
				CString pszFileName =_T("client.jpg");
				CFile myfile;
				try
				{
					myfile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite);
					myfile.Write(dataptr, Photo.m_pbinary->m_dwDataLength);
					myfile.Close();
					GlobalUnlock(Photo.m_pbinary->m_hData);
				}
				catch (const std::exception&)
				{
					GlobalUnlock(Photo.m_pbinary->m_hData);
				}
			}
			cr.Close();
		}
	
}

void condition::Status::ChangeCurrentStatus(CurrentStatus status)
{
	shareData = status;
}

condition::Status::CurrentStatus condition::Status::GetCurrentStatus()
{
	
	return shareData; 
}